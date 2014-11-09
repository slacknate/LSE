#ifndef LSE_BUFFER_H
#define LSE_BUFFER_H

#include <new>
#include <iostream>
#include "lse/mutex.h"
#include "lse/semaphore.h"

namespace LSE {

/*
Generic thread-safe ring buffer template class for
writing a buffer for any sort of data type!
*/
template <class T> class Buffer {
    
    private:
        
        Mutex read_pos_lock; // lock for buffer read position
        Mutex write_pos_lock; // lock for buffer write position
        Semaphore read_write_sync; // semaphore to ensure the buffer cannot overrite itself
        
        const unsigned int size; // size of the buffer
        
        unsigned int _read_pos; // actual read position
        unsigned int _write_pos; // actual write position
        
        T **buffer; // the actual buffer memory!
        
        /*
        Get the current buffer read position.
        */
        unsigned int read_pos() {
            
            read_pos_lock.Lock();
            
            unsigned int pos = this->_read_pos;
            
            ++this->_read_pos;
            if(this->_read_pos >= this->size)
                this->_read_pos = 0;
            
            read_pos_lock.Unlock();
            
            return pos;   
        }
        
        /*
        Get the current buffer write position.
        */
        unsigned int write_pos() {
            
            write_pos_lock.Lock();
            
            unsigned int pos = this->_write_pos;
            
            ++this->_write_pos;
            if(this->_write_pos >= this->size)
                this->_write_pos = 0;
            
            write_pos_lock.Unlock();
            
            return pos;   
        }
        
    public:
        
        /*
        Initialze the buffer size, buffer memory, and semaphore initial value.
        */
        Buffer(unsigned int _size) : read_write_sync(_size), size(_size), buffer(new T *[_size]) {
            
            this->_read_pos = 0;
            this->_write_pos = 0;
        }
        
        /*
        Delete all items currently in the buffer, and clean up the
        remaining buffer memory.
        */
        ~Buffer() {
            
            this->flush();
            
            delete[] this->buffer;
        }
        
        /*
        Delete all items currently in the buffer.
        */
        void flush() {
            
            read_pos_lock.Lock();
            write_pos_lock.Lock();
            
            for(unsigned int i = 0; i < this->size; ++i) {
                
                if(this->buffer[i] != nullptr) {
                    
                    delete this->buffer[i];
                }
            }
            
            write_pos_lock.Unlock();
            read_pos_lock.Unlock();
        }
        
        /*
        Write to the buffer.
        */
        void push(const T &t) {
            
            read_write_sync.wait();
            
            unsigned int pos = this->write_pos();
            this->buffer[pos] = new (std::nothrow) T(t);
            
            if(this->buffer[pos] == nullptr) {
                
                // raise exception here
            }
        }
        
        /*
        Read from the buffer.
        */
        T* pop() {
            
            unsigned int pos = this->read_pos();
            T *t = this->buffer[pos];
            this->buffer[pos] = nullptr;
            
            read_write_sync.post();
            
            return t;
        }        
};

}

#endif
