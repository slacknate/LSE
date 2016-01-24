#include "lse/event/types.h"
using namespace LSE;


/*
Initialize the type and name members of the Event.
*/
Event::Event(const EventType _type, const char *const _name) : type(_type), name(_name) {}


/*
Initialize a keyboard event.
*/
KeyEvent::KeyEvent() : Event(EVENT_KEYBOARD, "KeyEvent") {
            
    this->key = KEY_INVALID; 
}


/*
Initialize a mouse event.
*/
MouseEvent::MouseEvent() : Event(EVENT_MOUSE, "MouseEvent") {
            
    this->button = MOUSE_INVALID;
    this->dX = this->dY = this->dW = 0;
}


/*
Initialize a quit event.
*/
QuitEvent::QuitEvent() : Event(EVENT_QUIT, "QuitEvent") {
            
    this->status = StatusCode();
}
