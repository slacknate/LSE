#include "lse/object.h"
#include "lse/globals.h"
using namespace LSE;

/*
Initialize our map pointer.
*/
Object::Object() : table_ptr(nullptr) {}


/*
We have a virtual destructor so that if we ever
delete an object which is pointed to by a base class pointer
all destructors get called to properly tear down the object.
*/
Object::~Object() {}


/*
Register an event table for this object.
*/
void Object::register_table(const EventTableBase *tp) {
            
    this->table_ptr = tp;
}


/*
Dispatch an event through the event table.
*/
int Object::dispatch(Object *sender, unsigned int type, unsigned int id, void *ptr) {
    
    int result = 0;
    if(this->table_ptr != nullptr)
        result = this->table_ptr->dispatch(this, sender, type, id, ptr);
        
    else
        logger.error("This object does not have an event table.\nSkipping event dispatch.");
    
    return result;
}
