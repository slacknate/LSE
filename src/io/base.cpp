#include "io/base.h"
using namespace LSE;

Object *IOHandlerBase::engine = nullptr;

IOHandlerBase::IOHandlerBase(Object *_engine) {

    IOHandlerBase::engine = _engine;
}

void IOHandlerBase::publish(Event *event) {

    IOHandlerBase::engine->publish(event);
}
