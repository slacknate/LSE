#include "io/win.h"
#include "gui/window/win.h"

LSE_GLWindow_Win::LSE_GLWindow_Win(const char *const windowTitle, unsigned int mask,
                                   int width, int height, double angle, double zi, double za) : 
                                   LSE_GLWindow_Base(windowTitle, mask, width, height, angle, zi, za) { }

void LSE_GLWindow_Win::GLContextInit() {
    
    wglMakeCurrent(hdc, hglrc);
}

void LSE_GLWindow_Win::GLContextDestroy() {
    
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc); // this is an issue, HWND is destroyed before we get here....
}

void LSE_GLWindow_Win::SwapGLBuffers() {
    
    SwapBuffers(hdc);
}

/*
Create a window with an OpenGL context,
and run our UI event loop.
*/
void* LSE_GLWindow_Win::Execute() {
    
    LSE_TRY()
    
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
        LSE_THROW(LSE_WIN_REG_FAIL);
    
    // Create our window
    hwnd = CreateWindow(wc.lpszClassName, windowTitle, WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, width, height, NULL, NULL, wc.hInstance, NULL);
    if(hwnd == NULL)
        LSE_THROW(LSE_WIN_CREATE_FAIL);
        
    this->handler->Setup(hwnd);
    
    // Get a device context so we can use OpenGL
    hdc = GetDC(hwnd);
    if(hdc == NULL)
        LSE_THROW(LSE_GL_CON_FAIL);
    
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
        LSE_THROW(LSE_GL_CON_FAIL);
    
    hglrc = wglCreateContext(hdc);
    if(hglrc == NULL)
        LSE_THROW(LSE_GL_CON_FAIL);
    
    initialized = true;
    
    // Begin the message queue
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    LSE_CATCH()
}
