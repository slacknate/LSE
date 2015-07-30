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

    if(sem_init(&this->semaphore, shared, initial))
        throw EXCEPTION("Failed to initialize semaphore");
}


/*
Destroy the semaphore.
*/
Semaphore::~Semaphore() {
    
    if(sem_destroy(&this->semaphore))
        logger.errn("An error occurred in sem_destroy");
}


/*
Wait on the semaphore.
*/
void Semaphore::wait() {
    
    if(sem_wait(&this->semaphore))
        throw EXCEPTION("An error occurred in sem_wait");
}


/*
Attempt to non-blocking wait on the semaphore.
*/
bool Semaphore::try_wait() {

    bool success = true;

    int result = sem_trywait(&this->semaphore);
    if(result < 0) {

        if(errno == EAGAIN)
            success = false;

        else
            throw EXCEPTION("An error occurred in sem_trywait");
    }

    return success;
}


/*
Post to the semaphore.
*/
void Semaphore::post() {

    if(sem_post(&this->semaphore))
        throw EXCEPTION("An error occurred in sem_post");
}


/*
Get the current number of available wait slots available.
*/
int Semaphore::value() {
    
    int current_value = 0;
    
    if(sem_getvalue(&this->semaphore, &current_value))
        throw EXCEPTION("An error occurred in sem_getvalue");

    return current_value;
}
