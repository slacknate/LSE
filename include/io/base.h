#ifndef LSE_IO_HANDLER_BASE_H
#define LSE_IO_HANDLER_BASE_H

#include "lse/object.h"

class LSE_IOHandler_Base : public LSE_Object {
    
    friend class LSE_Engine; // FIXME: many hacks, such wow
    
    private:
        
        static LSE_Object *engine;
        
    public:
        
        static void HandleEvent(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr);
};

#endif
