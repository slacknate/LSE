#ifndef TEST_CAM_H
#define TEST_CAM_H

#include "gui/window/window.h"

namespace LSE {

// test camera manipulation object
class TestCam : public Object {
    
    private:
    
        GLWindow *window; // system provided opengl context
    
    public:
        
        TestCam(GLWindow *w);
        
        enum {
            
            ID_KEY = 1
        };
        
        int OnKey(Event *);
};

}

#endif
