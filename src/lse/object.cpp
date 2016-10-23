#include "lse/object.h"
#include "lse/globals.h"
/* Every object type which subscribes to an event needs to be included here. */
#include "lse/thread.h"
using namespace LSE;


/*
 * Mutex to disallow multiple
 * objects from pushing to the
 * event queue at the same time.
 */
Mutex Object::queue_mutex;


/*
 * Semaphore to disallow popping
 * events from an empty queue.
 */
Semaphore Object::event_sem;


/*
 * Object-global event queue.
 */
EventQueue Object::event_queue;


/*
 * Object-global event map.
 */
EventHandlersMap Object::event_map;


/*
 * We have a virtual destructor so that if we ever
 * delete an object which is pointed to by a base class pointer
 * all destructors get called to properly tear down the object.
 */
Object::~Object() {}


/*
 *
 */
void Object::handle(Event *event, Object *target, EventTopic topic) {

    EventHandlersMap::const_iterator handler_it = Object::event_map.find(event->type);
    if(handler_it != Object::event_map.end()) {

        EventHandlers *handlers = handler_it->second;
        for(size_t i = 0; i < handlers->size(); ++i) {

            EventHandlerBase *handler = handlers->at(i);
            Object *handler_obj = handler->obj;

            if(target == nullptr) {

                handler_obj->consume(event, handler);
            }
            else if(target == handler_obj) {

                handler_obj->consume(event, handler);
                break;  // FIXME: OH MAH GOD THIS IS TABOO @*)#$&%)*(@#$&%(*@#&$%@#N!!!1
            }
        }
    }
}

/*
 * FIXME: figure out how to implement and do proper cast!
 */
//void Object::consume(Event *event, EventHandlerBase *event_handler) {
//
//    this->consume_as< ??? >(event, event_handler);
//
//    logger.verbose("Event consumed.");
//}


/*
 * Publish an event to the event queue.
 */
void Object::publish(Event *event, Object *target, EventTopic topic) {

    if(event != nullptr) {

        struct EventContainer *container = new struct EventContainer;

        container->event = event;
        container->target = target;
        container->topic = topic;

        Object::queue_mutex.lock();
        Object::event_queue.push(container);
        Object::queue_mutex.unlock();

        Object::event_sem.post();

        logger.verbose("Pushed %s to the event queue.", event->name);
    }
    else {

        logger.error("Cannot push NULL event to the event queue.");
    }
}
