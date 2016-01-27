#ifndef LSE_OBJECT_H
#define LSE_OBJECT_H

#include <queue>
#include "lse/defs.h"
#include "lse/mutex.h"
#include "lse/event/table.h"

namespace LSE {

typedef std::queue<Event*> EventQueue;


/*
Base class for all Lucent Shards Engine objects.
*/
class Object {

    private:

        static Mutex event_mutex;
        static EventTable event_table;
        static EventQueue event_queue;

    protected:

        /*
        * Subscribe to the given event type using
        * the given class method to handle the events.
        */
        template <class T> void subscribe(const EventType type, void (T::*const method)(Event *)) {

            event_table.subscribe<T>(type, method);
        }

    public:
        
        virtual ~Object();
        
        void publish(Event *event);
};

}

#endif
