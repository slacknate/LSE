#ifndef LSE_THREAD_H
#define LSE_THREAD_H

#include <pthread.h>
#include "lse/object.h"

namespace LSE {

/*
Thread class used to create objects
which can run an additional thread in the
background but still respond to events.
*/
class Thread : public Object {
    
    DECLARE(Thread)
       
    protected:
        
        pthread_t thread; // event loop thread ID
        bool execute; // thread execution state
        
        static void* ThreadMethod(void *arg);
        
    public:
        
        Thread();
        
        bool Start();
        bool Detach();
        bool Join();
        
        virtual void* Execute();
        
        enum {
            
            ID_QUIT = 1
        };
        
        bool OnQuit(Object *sender, unsigned int type, unsigned int id, void *ptr);
};

}

#endif
