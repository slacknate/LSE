#include "lse/thread.h"
#include "lse/globals.h"
#include "lse/exception.h"
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

    void *result = nullptr;

    try {

        Thread *thread = (Thread *)arg;
        result = thread->execute();
    }
    catch(std::exception &e) {

        logger.error(e.what());
    }

    return result;
}

/*
Run the thread.
*/
bool Thread::start() {
    
    int thread_error = pthread_create(&thread, NULL, &Thread::thread_method, this);
    if(thread_error != 0)
        logger.errn("Error starting thread");
        
    else
        running = true;
        
    return !thread_error;
}

/*
Detach the thread from the calling thread.
*/
bool Thread::detach() {
    
    int thread_error = pthread_detach(thread);
    if(thread_error != 0)
        logger.errn("Error detaching thread");
        
    return !thread_error;
}

/*
Join the thread to the calling thread.
*/
bool Thread::join() {
    
    running = false;
    
    int thread_error = pthread_join(thread, NULL);
    if(thread_error != 0)
        logger.errn("Error joining thread");
        
    return !thread_error;
}

/*
Give the user the ability to terminate
a detached thread.
*/
int Thread::on_quit(Object *, unsigned int, unsigned int, void *) {
    
    running = false;
    return true;
}
