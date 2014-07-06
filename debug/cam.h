#ifndef TEST_CAM_H
#define TEST_CAM_H

#include "gui/window/window.h"

namespace LSE {

// test camera manipulation object
class TestCam : public Object {
    
    DECLARE(TestCam)
    
    private:
    
        GLWindow *window; // system provided opengl context
    
    public:
        
        TestCam(GLWindow *w);
        
        enum {
            
            ID_KEY = 1
        };
        
        bool OnKey(Object *o, unsigned int type, unsigned int id, void *ptr);
};

}

#endif
