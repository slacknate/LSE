#ifndef LSE_MUTEX_H
#define LSE_MUTEX_H

#include <pthread.h>

namespace LSE {

/*

*/
class LSE_Mutex {
    
    private:
        
        pthread_mutex_t mutex; // thread mutex
        bool initialized; // state of the mutex. true when pthread_mutex_init succeeds
        
    public:
        
        LSE_Mutex();
        ~LSE_Mutex();
        
        void Lock();
        void TryLock();
        void Unlock();
};

}

#endif
