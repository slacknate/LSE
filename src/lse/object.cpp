#include "lse/object.h"
#include "lse/globals.h"
using namespace LSE;


/*
 * Mutex for protecting the integrity of the event queue.
 */
Mutex Object::event_mutex;

/*
 * Object-global event table.
 */
EventTable Object::event_table;

/*
 * Object-global event queue.
 */
EventQueue Object::event_queue;


/*
 * We have a virtual destructor so that if we ever
 * delete an object which is pointed to by a base class pointer
 * all destructors get called to properly tear down the object.
 */
Object::~Object() {}


/*
 * Publish an event to the event queue.
 */
void Object::publish(Event *event) {

    if(event != nullptr) {

        Object::event_mutex.Lock();
        Object::event_queue.push(event);
        Object::event_mutex.Unlock();

        logger.debug("Pushed %s event to the event queue.", event->name);
    }
    else {

        logger.error("Cannot push NULL event to the event queue.");
    }
}
