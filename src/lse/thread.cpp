#include "lse/thread.h"
using namespace LSE;

/*
LSE_Thread event table.
*/
LSE_EVTMAP(LSE_Thread) ThreadMap[] = {
    
    LSE_EVTFUNC(LSE_QUIT, LSE_Thread::ID_QUIT, LSE_Thread::OnQuit)
};

/*
Event handler implementation.
*/
LSE_EVTIMP(LSE_Thread, ThreadMap)

/*
Initialize our thread to a non-running state.
*/
LSE_Thread::LSE_Thread() {
    
    execute = false;
}

/*
Run the user defined method in the new thread.
*/
void* LSE_Thread::ThreadMethod(void *arg) {
    
    LSE_Thread *t = (LSE_Thread *)arg;
    return t->Execute();
}

/*
Run the thread.
*/
bool LSE_Thread::Start() {
    
    int threadError = pthread_create(&thread, NULL, &LSE_Thread::ThreadMethod, this);
    if(threadError != 0)
        ERRNO("Error starting thread");
    else
        execute = true;
        
    return !threadError;
}

/*
Detach the thread from the calling thread.
*/
bool LSE_Thread::Detach() {
    
    int threadError = pthread_detach(thread);
    if(threadError != 0)
        ERRNO("Error detaching thread");
        
    return !threadError;
}

/*
Join the thread to the calling thread.
*/
bool LSE_Thread::Join() {
    
    execute = false;
    
    int threadError = pthread_join(thread, NULL);
    if(threadError != 0)
        ERRNO("Error joining thread");
        
    return !threadError;
}

/*

*/
void* LSE_Thread::Execute() { 
    
    return NULL;
}

/*
Give the user the ability to terminate
a detached thread.
*/
bool LSE_Thread::OnQuit(LSE_Object *, unsigned int, unsigned int, void *) {
    
    execute = false;
    return true;
}
