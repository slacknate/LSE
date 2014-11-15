#ifndef LSE_EVENT_TABLE_H
#define LSE_EVENT_TABLE_H

#include <vector> // FIXME: don't use STL stuff...
#include "lse/event/entry.h"
#include "lse/event/types.h"

namespace LSE {
    
/*
Forward declaration of LSE::Object so 
we do not end up with circular inclusion.
*/
class Object;

/*
Base class for an objects' event table.
*/
class EventTableBase {
    
    public:
        
        virtual int dispatch(Object *, Object *, unsigned int, unsigned int, void *) const { return 0; }
};


/*
Class that is used to implement an objects' event table.
*/
template <class T> class EventTable : public EventTableBase {
    
    private:
        
        typedef int (T::*EventMethod)(Object *, unsigned int, unsigned int, void *);
        
        std::vector< EventTableEntry<T> > items;
    
    public:
        
        EventTable(std::initializer_list< EventTableEntry<T> > _items) {
                        
            unsigned int i = 0;
            typename std::initializer_list< EventTableEntry<T> >::iterator curr;
            for(curr = _items.begin(); curr != _items.end(); ++curr, ++i) {
                
                this->items.push_back(*curr);
            }
        }
        
        int dispatch(Object *target, Object *sender, unsigned int type, unsigned int id, void *ptr) const {
            
            T *typed_target = (T *)target;
            
            int result = 0;
            for(int i = 0; i < this->items.size(); ++i) {
                
                const EventTableEntry<T> &table_entry = this->items[i];
                
                const unsigned int handler_type = table_entry.type;
                const unsigned int handler_id = table_entry.id;
                const EventMethod handler_method = table_entry.method;
                
                if((handler_type == type || handler_type == EVENT_ANY) && (handler_id == id || handler_id == ID_ANY)) {
                    
                    result = (typed_target->*(handler_method))(sender, type, id, ptr);
                }
            }
            
            return result; 
        }
};

}

#endif
