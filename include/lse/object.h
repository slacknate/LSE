#ifndef LSE_OBJECT_H
#define LSE_OBJECT_H

#include <map>
#include <queue>
#include <vector>
#include "lse/defs.h"
#include "lse/mutex.h"
#include "lse/semaphore.h"
#include "lse/event/types.h"
#include "lse/event/handler.h"
#include "lse/event/targets.h"

namespace LSE {


struct EventContainer {

    Event *event;
    Object *target;
    EventTopic topic;
};

typedef std::queue<struct EventContainer*> EventQueue;

typedef std::vector<EventHandlerBase*> EventHandlers;
typedef std::map<EventType, EventHandlers*> EventHandlersMap;


/*
Base class for all Lucent Shards Engine objects.
*/
class Object {

    private:

        // FIXME: aside from the Engine friend class crap these don't need to be members...
        static Mutex queue_mutex;
        static Semaphore event_sem;
        static EventQueue event_queue;
        static EventHandlersMap event_map;

        static void handle(Event *event, Object *target, EventTopic topic);

    protected:

        /*
         * Subscribe to the given event type using
         * the given class method to handle the events.
         */
        template <class T> void subscribe(const EventType type, void (T::*const method)(Event *), EventTopic topic=TOPIC_ANY) {

            if(Object::event_map.count(type) < 1)
                Object::event_map[type] = new EventHandlers();

            Object::event_map[type]->push_back(new EventHandler<T>(type, (T *const)this, method, topic));
        }

        virtual EventTarget get_target();

    public:
        
        virtual ~Object();

        void consume(Event *event, EventHandlerBase *event_handler);
        void publish(Event *event, Object *target=nullptr, EventTopic topic=TOPIC_ANY);

    friend class Engine;  // FIXME: this is some jank... whoops!
};

}

#endif
