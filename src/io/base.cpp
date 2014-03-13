#include "io/base.h"

LSE_Object *LSE_IOHandler_Base::engine = NULL;

void LSE_IOHandler_Base::HandleEvent(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr) {
    
    LSE_IOHandler_Base::engine->Dispatch(sender, type, id, ptr);
}
