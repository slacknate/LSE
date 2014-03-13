#include "lse/mutex.h"
#include "lse/defs.h"

/*
Initialize our mutex.
*/
LSE_Mutex::LSE_Mutex() {
    
    initialized = !pthread_mutex_init(&mutex, NULL);
    if(!initialized)
        LSE_ERRNO_LOG("Failed to initialize mutex");
}

/*
Destroy the mutex.
*/
LSE_Mutex::~LSE_Mutex() {
    
    if(initialized) {
        
        if(pthread_mutex_destroy(&mutex))
            LSE_ERRNO_LOG("Failed to destroy mutex");
    }
}

/*
Lock the mutex.
*/
void LSE_Mutex::Lock() {
    
    if(initialized) {
        
        if(pthread_mutex_lock(&mutex))
            LSE_ERRNO_LOG("Failed to lock mutex");
    }
}

/*
Attempt a non-blocking lock on the mutex.
*/
void LSE_Mutex::TryLock() {
    
    if(initialized) {
        
        if(pthread_mutex_trylock(&mutex))
            LSE_ERRNO_LOG("Failed trying mutex lock");
    }
}

/*
Unlock the mutex.
*/
void LSE_Mutex::Unlock() {
    
    if(initialized) {
        
        if(pthread_mutex_unlock(&mutex))
            LSE_ERRNO_LOG("Failed to unlock mutex");
    }
}
