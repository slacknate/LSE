#include "lse/object.h"

/*
Event handler method.
Overridden by classes which
implement an event table.
*/
bool Object::Dispatch(Object *, unsigned int, unsigned int, void *) {
    
    return false;
}
