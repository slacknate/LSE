#include "io/win.h"
#include "gui/window/win.h"
#include "lse/exception.h"
using namespace LSE;

GLWindow::GLWindow(const char *const windowTitle, unsigned int mask,
                           int width, int height, double angle, double zi, double za) : 
                           GLWindow_Base(windowTitle, mask, width, height, angle, zi, za) { }

void GLWindow::GLContextInit() {
    
    wglMakeCurrent(hdc, hglrc);
}

void GLWindow::GLContextDestroy() {
    
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc); // this is an issue, HWND is destroyed before we get here....
}

void GLWindow::SwapGLBuffers() {
    
    SwapBuffers(hdc);
}

/*
Create a window with an OpenGL context,
and run our UI event loop.
*/
void* GLWindow::Execute() {
    
    try {
    
    // Create a window class to be used for CreateWindow
    WNDCLASS wc;
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = &this->handler->WindowHandler;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Lucent Shards Engine";
    if(!RegisterClass(&wc))
        throw Exception(__FILE__, __LINE__, WIN_REG_FAIL);
    
    // Create our window
    hwnd = CreateWindow(wc.lpszClassName, windowTitle, WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, width, height, NULL, NULL, wc.hInstance, NULL);
    if(hwnd == NULL)
        throw Exception(__FILE__, __LINE__, WIN_CREATE_FAIL);
        
    this->handler->Setup(hwnd);
    
    // Get a device context so we can use OpenGL
    hdc = GetDC(hwnd);
    if(hdc == NULL)
        throw Exception(__FILE__, __LINE__, GL_CON_FAIL);
    
    // Set up all out IO for this window
    //io.Setup(hwnd);
    
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
        throw Exception(__FILE__, __LINE__, GL_CON_FAIL);
    
    hglrc = wglCreateContext(hdc);
    if(hglrc == NULL)
        throw Exception(__FILE__, __LINE__, GL_CON_FAIL);
    
    initialized = true;
    
    // Begin the message queue
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    }
    catch(std::exception &e) {
        
        throw Exception(__FILE__, __LINE__, OK); // FIXME: need a way to "convert" standard exceptions into LSE exceptions
    }
    
    return NULL;
}
