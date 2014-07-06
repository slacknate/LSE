#include "lse/semaphore.h"
#include "lse/defs.h"
using namespace LSE;

/*
Initialize our semaphore.
Set shared and initial value parameters,
and if we have a desired max value,
store that as well.
*/
Semaphore::Semaphore(int initial, int shared) {
    
    initialized = !sem_init(&semaphore, shared, initial);
    if(!initialized)
        ERRNO("Failed to initialize semaphore");
}

/*
Destroy the semaphore.
*/
Semaphore::~Semaphore() {
    
    if(initialized) {
        
        if(sem_destroy(&semaphore))
            ERRNO("Failed to destroy semaphore");
    }
}

/*
Wait on the semaphore.
*/
void Semaphore::Wait() {
    
    if(initialized) {
        
        if(sem_wait(&semaphore))
            ERRNO("Failed to wait on semaphore");
    }
}

/*
Attempt to non-blocking wait on the semaphore.
*/
void Semaphore::TryWait() {
    
    if(initialized) {
        
        if(sem_trywait(&semaphore))
            ERRNO("Failed to try to wait on semaphore");
    }
}

/*
Post to the semaphore.
*/
void Semaphore::Post() {
    
    if(initialized) {
        
        if(sem_post(&semaphore))
            ERRNO("Failed to post to semaphore");
    }
}

/*
Get the current number of available wait slots available.
*/
int Semaphore::Value() {
    
    int currValue = 0;
    
    if(initialized) {
        
        if(sem_getvalue(&semaphore, &currValue))
            ERRNO("Failed to get current semaphore value");
    }    
    
    return currValue;
}
