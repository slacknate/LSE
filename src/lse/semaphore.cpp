#include "lse/semaphore.h"
#include "lse/defs.h"

/*
Initialize our semaphore.
Set shared and initial value parameters,
and if we have a desired max value,
store that as well.
*/
LSE_Semaphore::LSE_Semaphore(int initial, int shared) {
    
    initialized = !sem_init(&semaphore, shared, initial);
    if(!initialized)
        LSE_ERRNO_LOG("Failed to initialize semaphore");
}

/*
Destroy the semaphore.
*/
LSE_Semaphore::~LSE_Semaphore() {
    
    if(initialized) {
        
        if(sem_destroy(&semaphore))
            LSE_ERRNO_LOG("Failed to destroy semaphore");
    }
}

/*
Wait on the semaphore.
*/
void LSE_Semaphore::Wait() {
    
    if(initialized) {
        
        if(sem_wait(&semaphore))
            LSE_ERRNO_LOG("Failed to wait on semaphore");
    }
}

/*
Attempt to non-blocking wait on the semaphore.
*/
void LSE_Semaphore::TryWait() {
    
    if(initialized) {
        
        if(sem_trywait(&semaphore))
            LSE_ERRNO_LOG("Failed to try to wait on semaphore");
    }
}

/*
Post to the semaphore.
*/
void LSE_Semaphore::Post() {
    
    if(initialized) {
        
        if(sem_post(&semaphore))
            LSE_ERRNO_LOG("Failed to post to semaphore");
    }
}

/*
Get the current number of available wait slots available.
*/
int LSE_Semaphore::Value() {
    
    int currValue = 0;
    
    if(initialized) {
        
        if(sem_getvalue(&semaphore, &currValue))
            LSE_ERRNO_LOG("Failed to get current semaphore value");
    }    
    
    return currValue;
}
