#ifndef TEST_PRISM_H
#define TEST_PRISM_H

#include "gl/rectprism.h"
#include "gui/window/window.h"

namespace LSE {

// test lse_globject class
class TestPrism : public GLRectPrism {
    
    DECLARE(TestPrism)
    
    private:
        
        GLWindow *window; // system provided opengl context
    
    public:
        
        TestPrism(GLWindow *win, double x, double y, double z, double w, double h, double d);
        
        enum {
            
            ID_MOUSE = 1,
            ID_KEY
        };
        
        bool OnMouseMotion(Object *sender, unsigned int type, unsigned int id, void *ptr);
        bool OnKey(Object *o, unsigned int type, unsigned int id, void *ptr);
};

}

#endif
