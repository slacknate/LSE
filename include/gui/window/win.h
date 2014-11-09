#ifndef LSE_GL_WINDOW_WIN_H
#define LSE_GL_WINDOW_WIN_H

#include "gui/window/base.h"

namespace LSE {

/*

*/
class GLWindow : public GLWindow_Base {
    
    private:
        
        HWND hwnd;
        HGLRC hglrc;
        HDC hdc;

        void setup_gl_context();
        void teardown_gl_context();
        void swap_gl_buffers();
        
    public:
        
        GLWindow(const char *const title, unsigned int m, int w, int h, double angle, double zi, double za);

        void* Execute();
};

}

#endif
