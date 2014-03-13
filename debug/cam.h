#ifndef TEST_CAM_H
#define TEST_CAM_H

#include "gui/window/window.h"

// test camera manipulation object
class TestCam : public LSE_Object {
    
    LSE_DECLARE(TestCam)
    
    private:
    
        LSE_GLWindow *window; // system provided opengl context
    
    public:
        
        TestCam(LSE_GLWindow *w);
        
        enum {
            
            ID_KEY = 1
        };
        
        bool OnKey(LSE_Object *o, unsigned int type, unsigned int id, void *ptr);
};

#endif
