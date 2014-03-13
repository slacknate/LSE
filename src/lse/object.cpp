#include "lse/object.h"

/*
Event handler method.
Overridden by classes which
implement an event table.
*/
bool LSE_Object::Dispatch(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr) {
    
    return false;
}
