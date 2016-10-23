#ifndef LSE_BUFFER_H
#define LSE_BUFFER_H

#include <new>
#include "lse/mutex.h"
#include "lse/semaphore.h"

namespace LSE {

/*
 * Generic thread-safe ring buffer template class for
 * writing a buffer for any sort of data type!
 */
template <class T> class Buffer {
    
    private:
        
        Mutex read_lock; // lock for buffer read position
        Mutex write_lock; // lock for buffer write position
        Semaphore read_sem; // semaphore to ensure the buffer read past existing data
        Semaphore write_sem; // semaphore to ensure the buffer cannot overwrite itself

        const unsigned int size; // size of the buffer
        
        unsigned int read_pos; // actual read position
        unsigned int write_pos; // actual write position
        
        T **buffer; // the actual buffer memory!
        
        /*
         * Modularly increment the read pointer based on buffer size.
         */
        void inc_read_pos() {

            ++this->read_pos;
            if(this->read_pos >= this->size)
                this->read_pos = 0;
        }
        
        /*
         * Modularly increment the write pointer based on buffer size.
         */
        void inc_write_pos() {
            
            ++this->write_pos;
            if(this->write_pos >= this->size)
                this->write_pos = 0;
        }
        
    public:
        
        /*
         * Initialize the buffer size and buffer memory.
         */
        Buffer(unsigned int _size) : size(_size), buffer(new T *[_size]) {
            
            /*
             * Initially read and write pointer both
             * point to our first item in the buffer.
             */
            this->read_pos = 0;
            this->write_pos = 0;

            /*
             * Initialize all our buffer items to nullptr.
             */
            memset(buffer, 0, _size);
        }
        
        /*
         * Delete all items currently in the buffer, and clean up the
         * remaining buffer memory.
         */
        ~Buffer() {
            
            this->flush();
            
            delete[] this->buffer;
        }
        
        /*
         * Delete all items currently in the buffer.
         */
        void flush() {

            read_lock.lock();
            write_lock.lock();
            
            for(unsigned int i = 0; i < this->size; ++i) {
                
                if(this->buffer[i] != nullptr) {
                    
                    delete this->buffer[i];
                    this->buffer[i] = nullptr;
                }
            }

            write_lock.unlock();
            read_lock.unlock();
        }
        
        /*
         * Write to the buffer.
         */
        void push(T *const t) {

            write_lock.lock();

            unsigned int pos = this->write_pos;
            this->inc_write_pos();

            write_lock.unlock();

            /*
             * If there is valid data in this location in
             * the buffer then we need to wait until the
             * reading caught up before we can write.
             */
            if(this->buffer[pos] != nullptr)
                this->write_sem.wait();

            this->buffer[pos] = t;

            /*
             * Post to the read semaphore when we push an
             * item into the buffer so we know we have
             * data available.
             */
            this->read_sem.post();
        }
        
        /*
         * Read from the buffer.
         */
        T *const pop() {

            read_lock.lock();

            unsigned int pos = this->read_pos;
            this->inc_read_pos();

            read_lock.unlock();

            if(this->buffer[pos] == nullptr)
                this->read_sem.wait();

            T *const t = this->buffer[pos];
            this->buffer[pos] = nullptr;

            /*
             * Post to the write semaphore when we pop an
             * item out of the buffer so we know we have
             * an open spot.
             */
            write_sem.post();

            return t;
        }        
};

}

#endif
