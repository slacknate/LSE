#include "lse/mutex.h"
#include "lse/defs.h"
using namespace LSE;

/*
Initialize our mutex.
*/
Mutex::Mutex() {
    
    initialized = !pthread_mutex_init(&mutex, NULL);
    if(!initialized)
        ERRNO("Failed to initialize mutex");
}

/*
Destroy the mutex.
*/
Mutex::~Mutex() {
    
    if(initialized) {
        
        if(pthread_mutex_destroy(&mutex))
            ERRNO("Failed to destroy mutex");
    }
}

/*
Lock the mutex.
*/
void Mutex::Lock() {
    
    if(initialized) {
        
        if(pthread_mutex_lock(&mutex))
            ERRNO("Failed to lock mutex");
    }
}

/*
Attempt a non-blocking lock on the mutex.
*/
void Mutex::TryLock() {
    
    if(initialized) {
        
        if(pthread_mutex_trylock(&mutex))
            ERRNO("Failed trying mutex lock");
    }
}

/*
Unlock the mutex.
*/
void Mutex::Unlock() {
    
    if(initialized) {
        
        if(pthread_mutex_unlock(&mutex))
            ERRNO("Failed to unlock mutex");
    }
}
