#ifndef LSE_IO_HANDLER_BASE_H
#define LSE_IO_HANDLER_BASE_H

#include "lse/object.h"

class LSE_IOHandler_Base : public LSE_Object {
    
    private:
        
        static LSE_Object *engine;
        
    public:
        
        LSE_IOHandler_Base(LSE_Object *e);
        
        static void HandleEvent(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr);
};

#endif
