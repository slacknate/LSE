#ifndef LSE_IO_HANDLER_BASE_H
#define LSE_IO_HANDLER_BASE_H

#include "lse/object.h"

namespace LSE {

/*

*/
class IOHandler_Base : public Object {
    
    private:
        
        static Object *engine;
        
    public:
        
        IOHandler_Base(Object *e);
        
        static void HandleEvent(Object *sender, unsigned int type, unsigned int id, void *ptr);
};

}

#endif
