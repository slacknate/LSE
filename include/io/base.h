#ifndef LSE_IO_HANDLER_BASE_H
#define LSE_IO_HANDLER_BASE_H

#include "lse/object.h"

namespace LSE {

/*

*/
class IOHandlerBase : public Object {
    
    private:
        
        static Object *engine;
        
    public:
        
        IOHandlerBase(Object *e);
        
        static void handle_event(Object *sender, unsigned int type, unsigned int id, void *ptr);
};

}

#endif
