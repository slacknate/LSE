#ifndef LSE_GL_WINDOW_BASE_H
#define LSE_GL_WINDOW_BASE_H

#include "gl/object.h"
#include "gl/program.h"
#include "gl/light.h"

#include "io/handler.h"
#include "lse/thread.h"
#include "gui/screen/screen.h"

/*
TODO:
    move version/attribute checking from engine run to context init
*/

namespace LSE {

/*
OpenGL context class.
Describes an OpenGL canvas, and
Draws all GLObjects.
*/
class GLWindow_Base : public Thread {
    
    protected:
        
        IOHandler *handler; // 
        List drawList; // list of objects to be drawn
        List lightList; // list of all lights in the scene
        GLScreen *screen; // 
        Vertex pos, focus; // camera position and focus point
        Vector up; // camera up vector
        
        bool initialized;
        //int glewStatus, glStatus; // return code of glewInit()
        const char *windowTitle;
        unsigned int width, height; // canvas width and height
        double fovy, zmin, zmax; // aspect ratio parameters
        unsigned int mask; // opengl bit clear mask
        
        void PlaceCamera();
        void AspectRatio();
        
    public:
        
        GLWindow_Base(const char *const windowTitle, unsigned int m, int w, int h, double angle, double zi, double za);
        ~GLWindow_Base();
        
        void SetupIO(IOHandler *h);
        
        void GLInit();
        virtual void GLContextInit() {}
        virtual void GLContextDestroy() {}
        
        void PushGL(GLObject *o);
        void PopGL();
        void ClearGL();
        
        void PushLight(GLLight *l);
        void PopLight();
        void ClearLights();
        
        void Render();
        virtual void SwapGLBuffers() {}
        
        Vertex& GetCamPos();
        Vertex& GetCamFocus();
        
        bool Ready();
        
        void Resize();
};

}

#endif
