#ifndef LSE_EVENT_TYPES_H
#define LSE_EVENT_TYPES_H

#include "lse/defs.h"

namespace LSE {

/*
LSE Event types.
*/
enum EventType : unsigned int {
    
    EVENT_ANY = 0,
    EVENT_KEYBOARD,
    EVENT_MOUSE,
    EVENT_INPUTOTHER,
    EVENT_VIDEO,
    EVENT_USER,
    EVENT_SYSTEM,
    EVENT_QUIT
};

/*
Base event class.
*/
class Event {
    
    public:
        
        const EventType type;
        const char *const name;
        
        Event(const EventType _type, const char *const _name);
};


/*
Event objects for keyboard input.
*/
class KeyEvent : public Event {
    
    public:
        
        bool state;
        unsigned int key;
        
        KeyEvent();
};


/*
Event object for mouse input.
*/
class MouseEvent : public Event {
    
    public:
        
        int dX, dY;
        short dW;
        bool state;
        unsigned int button;
        
        MouseEvent();
};


typedef struct {
    
    
}IOEvent;


typedef struct {
    
    
}VideoEvent;


typedef struct {
    
    
}UserEvent;


typedef struct {
    
    
}SysEvent;


/*
Event object for system/thread quit.
*/
class QuitEvent : public Event {
    
    public:
        
        unsigned int status;
        
        QuitEvent();
};

}

#endif
