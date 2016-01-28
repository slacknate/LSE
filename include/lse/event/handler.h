#ifndef LSE_EVENT_TABLE_ENTRY_H
#define LSE_EVENT_TABLE_ENTRY_H

#include "lse/event/types.h"
#include "lse/event/topics.h"

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

		Object *const obj;

		EventHandlerBase(Object *const _obj) : obj(_obj) {}
		virtual ~EventHandlerBase() {}
};


/*
Class which describes a single object event table entry/handler.
*/
template <class T> class EventHandler : public EventHandlerBase {

	public:

        const EventType type;
        void (T::*const method)(Event *);
		const EventTopic topic;

		EventHandler(const EventType _type, Object *const _obj, void (T::*const _method)(Event *), const EventTopic _topic) : EventHandlerBase(_obj), type(_type), method(_method), topic(_topic) {}
};

}

#endif
