#include "lse/thread.h"
#include "lse/globals.h"
using namespace LSE;

/*
Thread event table.
*/
const ThreadEventTable Thread::table = ThreadEventTable({

        ThreadTableEntry(EVENT_QUIT, Thread::ID_QUIT, &Thread::on_quit)
});

/*
Initialize our thread to a non-running state.
*/
Thread::Thread() {
    
    this->running = false;
    
    this->register_table(&Thread::table);
}

/*
Run the user defined method in the new thread.
*/
void* Thread::thread_method(void *arg) {
    
    Thread *thread = (Thread *)arg;
    return thread->execute();
}

/*
Run the thread.
*/
bool Thread::start() {
    
    int threadError = pthread_create(&thread, NULL, &Thread::thread_method, this);
    if(threadError != 0)
        logger.errn("Error starting thread");
        
    else
        running = true;
        
    return !threadError;
}

/*
Detach the thread from the calling thread.
*/
bool Thread::detach() {
    
    int threadError = pthread_detach(thread);
    if(threadError != 0)
        logger.errn("Error detaching thread");
        
    return !threadError;
}

/*
Join the thread to the calling thread.
*/
bool Thread::join() {
    
    running = false;
    
    int threadError = pthread_join(thread, NULL);
    if(threadError != 0)
        logger.errn("Error joining thread");
        
    return !threadError;
}

/*
Give the user the ability to terminate
a detached thread.
*/
int Thread::on_quit(Object *, unsigned int, unsigned int, void *) {
    
    running = false;
    return true;
}
