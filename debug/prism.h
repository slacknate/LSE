#ifndef TEST_PRISM_H
#define TEST_PRISM_H

#include "gl/rectprism.h"
#include "gui/window/window.h"

namespace LSE {

// test lse_globject class
class TestPrism : public GLRectPrism {
    
    private:
        
        GLWindow *window; // system provided opengl context
        bool grabbed;

        void calc_colors();
    
    public:
        
        TestPrism(GLWindow *win, float x, float y, float z, float w, float h, float d);
        
        enum {
            
            ID_MOUSE = 1,
            ID_KEY
        };
        
        void OnMouseMotion(Event *);
        void OnKey(Event *);

        /*
         * FIXME: implement in LSE::Object.
         */
        void consume(Event *event, EventHandlerBase *event_handler) {

            this->consume_as<TestPrism>(event, event_handler);
        }
};

}

#endif
