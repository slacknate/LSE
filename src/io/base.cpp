#include "io/base.h"
using namespace LSE;

Object *IOHandler_Base::engine = NULL;

IOHandler_Base::IOHandler_Base(Object *e) {
    
    this->engine = e;
}

void IOHandler_Base::HandleEvent(Object *sender, unsigned int type, unsigned int id, void *ptr) {
    
    IOHandler_Base::engine->Dispatch(sender, type, id, ptr);
}
