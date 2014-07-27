#ifndef LSE_EVENT_TABLE_ENTRY_H
#define LSE_EVENT_TABLE_ENTRY_H

namespace LSE {

/*
Constant that will match against any ID for an event handler.
*/    
const unsigned int ID_ANY = 0;
    
/*
Forward declaration of LSE::Object so 
we do not end up with circular inclusion.
*/
class Object;


/*
Class which describes a single object event table entry/handler.
*/
template <class T> class EventTableEntry {

	private:

		typedef int (T::*EventMethod)(Object *, unsigned int, unsigned int, void *);		
		
	public:
        
        const unsigned int type;
        const unsigned int id;
        const EventMethod method;

		EventTableEntry(unsigned int _type, unsigned int _id, EventMethod _method) : type(_type), id(_id), method(_method) {}
};

}

#endif
