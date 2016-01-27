#include "lse/mutex.h"
#include "lse/globals.h"
using namespace LSE;

/*
Initialize our mutex.
*/
Mutex::Mutex() {
    
    initialized = !pthread_mutex_init(&mutex, NULL);
    if(!initialized)
        logger.errn("Failed to initialize mutex");
}

/*
Destroy the mutex.
*/
Mutex::~Mutex() {
    
    if(initialized) {
        
        if(pthread_mutex_destroy(&mutex))
            logger.errn("Failed to destroy mutex");
    }
}

/*
Lock the mutex.
*/
void Mutex::lock() {
    
    if(initialized) {
        
        if(pthread_mutex_lock(&mutex))
            logger.errn("Failed to lock mutex");
    }
}

/*
Attempt a non-blocking lock on the mutex.
*/
void Mutex::try_lock() {
    
    if(initialized) {
        
        if(pthread_mutex_trylock(&mutex))
            logger.errn("Failed trying mutex lock");
    }
}

/*
Unlock the mutex.
*/
void Mutex::unlock() {
    
    if(initialized) {
        
        if(pthread_mutex_unlock(&mutex))
            logger.errn("Failed to unlock mutex");
    }
}
