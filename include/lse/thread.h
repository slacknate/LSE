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
    
    private:
        
        static const EventTable<Thread> table;
    
    protected:
        
        pthread_t thread; // event loop thread ID
        bool running; // thread execution state
        
        static void* thread_method(void *arg);
        
    public:
        
        Thread();
        
        bool start();
        bool detach();
        bool join();
        
        virtual void* execute()=0;
        
        enum {
            
            ID_QUIT = 1
        };
        
        int on_quit(Object *sender, unsigned int type, unsigned int id, void *ptr);
};

typedef EventTable<Thread> ThreadEventTable;
typedef EventTableEntry<Thread> ThreadTableEntry;

}

#endif
