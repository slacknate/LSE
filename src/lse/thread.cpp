#include "lse/thread.h"
using namespace LSE;

/*
Thread event table.
*/
const ThreadEventTable Thread::table = ThreadEventTable({
    
    ThreadTableEntry(EVENT_QUIT, Thread::ID_QUIT, &Thread::OnQuit)
});

/*
Initialize our thread to a non-running state.
*/
Thread::Thread() {
    
    this->execute = false;
    
    this->register_table(&Thread::table);
}

/*
Run the user defined method in the new thread.
*/
void* Thread::ThreadMethod(void *arg) {
    
    Thread *t = (Thread *)arg;
    return t->Execute();
}

/*
Run the thread.
*/
bool Thread::Start() {
    
    int threadError = pthread_create(&thread, NULL, &Thread::ThreadMethod, this);
    if(threadError != 0)
        ERRNO("Error starting thread");
    else
        execute = true;
        
    return !threadError;
}

/*
Detach the thread from the calling thread.
*/
bool Thread::Detach() {
    
    int threadError = pthread_detach(thread);
    if(threadError != 0)
        ERRNO("Error detaching thread");
        
    return !threadError;
}

/*
Join the thread to the calling thread.
*/
bool Thread::Join() {
    
    execute = false;
    
    int threadError = pthread_join(thread, NULL);
    if(threadError != 0)
        ERRNO("Error joining thread");
        
    return !threadError;
}

/*

*/
void* Thread::Execute() { 
    
    return NULL;
}

/*
Give the user the ability to terminate
a detached thread.
*/
int Thread::OnQuit(Object *, unsigned int, unsigned int, void *) {
    
    execute = false;
    return true;
}
