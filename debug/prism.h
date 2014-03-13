#ifndef TEST_PRISM_H
#define TEST_PRISM_H

#include "gl/rectprism.h"
#include "gui/window/window.h"

// test lse_globject class
class TestPrism : public LSE_GLRectPrism {
    
    LSE_DECLARE(TestPrism)
    
    private:
        
        LSE_GLWindow *window; // system provided opengl context
    
    public:
        
        TestPrism(LSE_GLWindow *win, double x, double y, double z, double w, double h, double d);
        
        enum {
            
            ID_MOUSE = 1,
            ID_KEY
        };
        
        bool OnMouseMotion(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr);
        bool OnKey(LSE_Object *o, unsigned int type, unsigned int id, void *ptr);
};

#endif
