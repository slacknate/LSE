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
        
    public:
        
        GLWindow(const char *const windowTitle, unsigned int m, int w, int h, double angle, double zi, double za);
        
        void GLContextInit();
        void GLContextDestroy();
        
        void SwapGLBuffers();
        
        void* Execute();
};

}

#endif
