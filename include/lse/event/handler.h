#ifndef LSE_EVENT_TABLE_ENTRY_H
#define LSE_EVENT_TABLE_ENTRY_H

#include "lse/event/types.h"

namespace LSE {

/*
Forward declaration of LSE::Object so 
we do not end up with circular inclusion.
*/
class Object;


/*
 *
 */
class EventHandlerBase {

	public:

		virtual ~EventHandlerBase() {}
};


/*
Class which describes a single object event table entry/handler.
*/
template <class T> class EventHandler : public EventHandlerBase {

	public:

        const EventType type;
        void (T::*const method)(Event *);

		EventHandler(const EventType _type, void (T::*const _method)(Event *)) : type(_type), method(_method) {}
};

}

#endif
