#ifndef LSE_EVENT_H
#define LSE_EVENT_H

/*
LSE Event types.
*/
enum {
    
    LSE_ANY = 0,
    LSE_KEYBOARD,
    LSE_MOUSE,
    LSE_INPUTOTHER,
    LSE_VIDEO,
    LSE_USER,
    LSE_SYSTEM,
    LSE_QUIT
};

/*
LSE_Event structures.
*/
class LSE_Event {
    
    public:
        
        unsigned int type;
};

class LSE_KeyEvent : LSE_Event {
    
    public:
        
        bool state;
        unsigned int key;
        
        LSE_KeyEvent() {
            
            this->type = LSE_KEYBOARD;
            this->key = LSE_KEY_INVALID; 
        }
};

class LSE_MouseEvent : LSE_Event {
    
    public:
        
        int dX, dY;
        short dW;
        bool state;
        unsigned int button;
        
        LSE_MouseEvent() {
            
            this->type = LSE_MOUSE;
            this->button = LSE_BUTTON_INVALID;
            this->dX = this->dY = this->dW = 0;
        }
};

typedef struct {
    
    
}LSE_IOEvent;

typedef struct {
    
    
}LSE_VideoEvent;

typedef struct {
    
    
}LSE_UserEvent;

typedef struct {
    
    
}LSE_SysEvent;

typedef struct {
    
    
}LSE_QuitEvent;

#endif
