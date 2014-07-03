#include "io/base.h"
using namespace LSE;

LSE_Object *LSE_IOHandler_Base::engine = NULL;

LSE_IOHandler_Base::LSE_IOHandler_Base(LSE_Object *e) {
    
    this->engine = e;
}

void LSE_IOHandler_Base::HandleEvent(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr) {
    
    LSE_IOHandler_Base::engine->Dispatch(sender, type, id, ptr);
}
