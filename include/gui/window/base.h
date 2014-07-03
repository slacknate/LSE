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
Draws all LSE_GLObjects.
*/
class LSE_GLWindow_Base : public LSE_Thread {
    
    protected:
        
        LSE_IOHandler *handler; // 
        LSE_List drawList; // list of objects to be drawn
        LSE_List lightList; // list of all lights in the scene
        LSE_GLScreen *screen; // 
        LSE_Vertex pos, focus; // camera position and focus point
        LSE_Vector up; // camera up vector
        
        bool initialized;
        //int glewStatus, glStatus; // return code of glewInit()
        const char *windowTitle;
        unsigned int width, height; // canvas width and height
        double fovy, zmin, zmax; // aspect ratio parameters
        unsigned int mask; // opengl bit clear mask
        
        void PlaceCamera();
        void AspectRatio();
        
    public:
        
        LSE_GLWindow_Base(const char *const windowTitle, unsigned int m, int w, int h, double angle, double zi, double za);
        ~LSE_GLWindow_Base();
        
        void SetupIO(LSE_IOHandler *h);
        
        void GLInit();
        virtual void GLContextInit() {}
        virtual void GLContextDestroy() {}
        
        void PushGL(LSE_GLObject *o);
        void PopGL();
        void ClearGL();
        
        void PushLight(LSE_GLLight *l);
        void PopLight();
        void ClearLights();
        
        void Render();
        virtual void SwapGLBuffers() {}
        
        LSE_Vertex& GetCamPos();
        LSE_Vertex& GetCamFocus();
        
        bool Ready();
        
        void Resize();
};

}

#endif
