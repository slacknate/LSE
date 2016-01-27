#ifndef LSE_IO_HANDLER_BASE_H
#define LSE_IO_HANDLER_BASE_H

#include "lse/object.h"

namespace LSE {

/*

*/
class IOHandlerBase {
    
    private:
        
        static Object *engine;
        
    public:
        
        IOHandlerBase(Object *_engine);
        
        static void publish(Event *event);
};

}

#endif
