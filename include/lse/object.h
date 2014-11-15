#ifndef LSE_OBJECT_H
#define LSE_OBJECT_H

#include "lse/defs.h"
#include "lse/event/table.h"

namespace LSE {


/*
Base class for all Lucent Shards Engine objects.
*/
class Object {
    
    private:
        
        const EventTableBase *table_ptr; // pointer to our event table
        
    protected:
        
        void register_table(const EventTableBase *tp);
    
    public:
        
        Object();

        virtual ~Object();
        
        int dispatch(Object *sender, unsigned int type, unsigned int id, void *ptr);
};

}

#endif
