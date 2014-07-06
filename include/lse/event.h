#ifndef LSE_EVENT_H
#define LSE_EVENT_H

#include "lse/defs.h"

namespace LSE {

/*
LSE Event types.
*/
typedef enum {
    
    ANY = 0,
    KEYBOARD,
    MOUSE,
    INPUTOTHER,
    VIDEO,
    USER,
    SYSTEM,
    QUIT
}EventType;

/*
Event structures.
*/
class Event {
    
    public:
        
        EventType type;
};

class KeyEvent : Event {
    
    public:
        
        bool state;
        unsigned int key;
        
        KeyEvent() {
            
            this->type = KEYBOARD;
            this->key = KEY_INVALID; 
        }
};

class MouseEvent : Event {
    
    public:
        
        int dX, dY;
        short dW;
        bool state;
        unsigned int button;
        
        MouseEvent() {
            
            this->type = MOUSE;
            this->button = MOUSE_INVALID;
            this->dX = this->dY = this->dW = 0;
        }
};

typedef struct {
    
    
}IOEvent;

typedef struct {
    
    
}VideoEvent;

typedef struct {
    
    
}UserEvent;

typedef struct {
    
    
}SysEvent;

typedef struct {
    
    
}QuitEvent;

}

#endif
