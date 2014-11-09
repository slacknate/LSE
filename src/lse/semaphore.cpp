#include "lse/globals.h"
#include "lse/exception.h"
#include "lse/semaphore.h"
using namespace LSE;

/*
Initialize our semaphore.
Set shared and initial value parameters,
and if we have a desired max value,
store that as well.
*/
Semaphore::Semaphore(int initial, int shared) {

    if(sem_init(&semaphore, shared, initial))
        throw Exception(__FILE__, __LINE__, "Failed to initialize semaphore");
}

/*
Destroy the semaphore.
*/
Semaphore::~Semaphore() {
    
    if(sem_destroy(&semaphore))
        logger.errn("Failed to destroy semaphore");
}

/*
Wait on the semaphore.
*/
void Semaphore::Wait() {
    
    if(sem_wait(&semaphore))
        logger.errn("Failed to wait on semaphore");
}

/*
Attempt to non-blocking wait on the semaphore.
*/
void Semaphore::TryWait() {
    
    if(sem_trywait(&semaphore))
        logger.errn("Failed to try to wait on semaphore");
}

/*
Post to the semaphore.
*/
void Semaphore::Post() {
    
   if(sem_post(&semaphore))
        logger.errn("Failed to post to semaphore");
}

/*
Get the current number of available wait slots available.
*/
int Semaphore::Value() {
    
    int currValue = 0;
    
    if(sem_getvalue(&semaphore, &currValue))
        logger.errn("Failed to get current semaphore value");

    return currValue;
}
