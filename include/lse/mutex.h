#ifndef LSE_MUTEX_H
#define LSE_MUTEX_H

#include <pthread.h>

namespace LSE {

/*

*/
class Mutex {
    
    private:
        
        pthread_mutex_t mutex; // thread mutex
        bool initialized; // state of the mutex. true when pthread_mutex_init succeeds
        
    public:
        
        Mutex();
        ~Mutex();
        
        void lock();
        void try_lock();
        void unlock();
};

}

#endif
