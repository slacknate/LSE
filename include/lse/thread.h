#ifndef LSE_THREAD_H
#define LSE_THREAD_H

#include <pthread.h>
#include "lse/object.h"

/*
Thread class used to create objects
which can run an additional thread in the
background but still respond to events.
*/
class LSE_Thread : public LSE_Object {
    
    LSE_DECLARE(LSE_Thread)
       
    protected:
        
        pthread_t thread; // event loop thread ID
        bool execute; // thread execution state
        
        static void* ThreadMethod(void *arg);
        
    public:
        
        LSE_Thread();
        
        bool Start();
        bool Detach();
        bool Join();
        
        virtual void* Execute();
        
        enum {
            
            ID_QUIT = 1
        };
        
        bool OnQuit(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr);
};

#endif
