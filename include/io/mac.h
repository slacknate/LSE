#ifndef LSE_IO_HANDLER_MAC_H
#define LSE_IO_HANDLER_MAC_H

#include "io/base.h"

class LSE_IOHandler_Mac : public LSE_IOHandler_Base {
        
    public:
        
        LSE_IOHandler_Mac(LSE_Object *e);
};

#define LSE_IOHandler LSE_IOHandler_Mac

#endif
