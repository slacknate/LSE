#include "io/base.h"
using namespace LSE;

Object *IOHandlerBase::engine = NULL;

IOHandlerBase::IOHandlerBase(Object *e) {
    
    this->engine = e;
}

void IOHandlerBase::handle_event(Object *sender, unsigned int type, unsigned int id, void *ptr) {

    IOHandlerBase::engine->dispatch(sender, type, id, ptr);
}
