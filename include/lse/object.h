#ifndef LSE_OBJECT_H
#define LSE_OBJECT_H

#include "lse/defs.h"

/*
Base class for all Lucent Shards Engine objects.
TODO: refactor Dispatch to return an int instead of a bool.
      returning real result codes would probably be a nice feature
      for an event handler.
*/
class LSE_Object {
    
    public:
        
        virtual bool Dispatch(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr);
};

#endif
