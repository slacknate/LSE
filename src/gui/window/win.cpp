#include "io/win.h"
#include "gui/window/win.h"
#include "lse/exception.h"
using namespace LSE;

GLWindow::GLWindow(const char *const title, unsigned int mask,
                           int width, int height, float angle, float zi, float za) :
                           GLWindowBase(title, mask, width, height, angle, zi, za) { }

void GLWindow::setup_gl_context() {
    
    wglMakeCurrent(hdc, hglrc);
}

void GLWindow::teardown_gl_context() {
    
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
}

void GLWindow::swap_gl_buffers() {
    
    SwapBuffers(hdc);
}

/*
Create a window with an OpenGL context,
and run our UI event loop.
*/
void* GLWindow::execute() {
    
    // Create a window class to be used for CreateWindow
    WNDCLASS wc;
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = &this->handler->window_proc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Lucent Shards Engine";
    if(!RegisterClass(&wc))
        throw EXCEPTION("Failed to register window class");
    
    // Create our window
    hwnd = CreateWindow(wc.lpszClassName, window_title, WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, width, height, NULL, NULL, wc.hInstance, NULL);
    if(hwnd == NULL)
        throw EXCEPTION("Failed to create window");
        
    this->handler->setup(hwnd);
    
    // Get a device context so we can use OpenGL
    hdc = GetDC(hwnd);
    if(hdc == NULL)
        throw EXCEPTION("Failed to obtain an OpenGL device context");
    
    PIXELFORMATDESCRIPTOR pfd = {
        
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,
        8,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };
    
    // Finish setting up our OpenGL context
    if(!SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd))
        throw EXCEPTION("Failed to set OpenGL context pixel format");
    
    hglrc = wglCreateContext(hdc);
    if(hglrc == NULL)
        throw EXCEPTION("Failed to create an OpenGL context");
    
    this->init_sem.post();
    
    // Begin the message queue
    MSG msg;
    while(GetMessage(&msg, hwnd, 0, 0)) {
        
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return nullptr;
}
