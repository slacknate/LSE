#ifndef LSE_IO_HANDLER_UNIX_H
#define LSE_IO_HANDLER_UNIX_H

#include "io/base.h"

class LSE_IOHandler_Nix : public LSE_IOHandler_Base {
        
    public:
        
        LSE_IOHandler_Nix(LSE_Object *e);
};

#define LSE_IOHandler LSE_IOHandler_Unix

#endif
