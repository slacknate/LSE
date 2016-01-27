#ifndef LSE_EVENT_TABLE_H
#define LSE_EVENT_TABLE_H

#include <map>
#include <vector>
#include "lse/event/handler.h"

namespace LSE {
    
/*
Forward declaration of LSE::Object so 
we do not end up with circular inclusion.
*/
class Object;

typedef std::vector< EventHandlerBase* > EventHandlers;
typedef std::map< const EventType, EventHandlers* > EventHandlersMap;


/*
Class that is used to implement an objects' event table.
*/
class EventTable {
    
    private:

        EventHandlersMap map;
    
    public:

        ~EventTable() {

            for(EventHandlersMap::iterator it = this->map.begin(); it != this->map.end(); ++it) {

                EventHandlers *handlers = it->second;

                while(!handlers->empty()) {

                    EventHandlerBase *handler = handlers->back();
                    handlers->pop_back();

                    delete handler;
                }

                delete handlers;
            }
        }

        template <class T> void subscribe(const EventType type, void (T::*const method)(Event *)) {

            if(this->map.count(type) < 1)
                this->map[type] = new EventHandlers();

            this->map[type]->push_back(new EventHandler<T>(type, method));
        }

        template <class T> void handle(Object *target, Event *event) const {

            T *typed_target = (T *)target;

            EventHandlersMap::const_iterator handler_it = this->map.find(event->type);

            if(handler_it != this->map.end()) {

                EventHandlers *handlers = handler_it->second;

                for(int i = 0; i < handlers->size(); ++i) {

                    const EventHandler<T> *const handler = (EventHandler<T> *)(*handlers)[i];
                    (typed_target->*(handler->method))(event);
                }
            }
        }
};

}

#endif
