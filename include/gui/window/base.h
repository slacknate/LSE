#ifndef LSE_GL_WINDOW_BASE_H
#define LSE_GL_WINDOW_BASE_H

#include "gl/light.h"
#include "gl/object.h"
#include "gl/program.h"

#include "io/handler.h"
#include "lse/thread.h"
#include "lse/semaphore.h"
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
class GLWindowBase : public Thread {
    
    protected:
        
        IOHandler *handler; // 
        List draw_list; // list of objects to be drawn
        List light_list; // list of all lights in the scene
        GLScreen *screen; // 
        Vertex pos, focus; // camera position and focus point
        Vector up; // camera up vector
        
        Semaphore init_sem;
        //int glewStatus, glStatus; // return code of glewInit()
        const char *window_title;
        unsigned int width, height; // canvas width and height
        double fovy, zmin, zmax; // aspect ratio parameters
        unsigned int mask; // opengl bit clear mask
        
        void PlaceCamera();
        void AspectRatio();

        virtual void setup_gl_context()=0;
        virtual void teardown_gl_context()=0;
        virtual void swap_gl_buffers()=0;

    public:

        GLWindowBase(const char *const title, unsigned int m, int w, int h, double angle, double zi, double za);

        void SetupIO(IOHandler *h);

        void setup_gl();
        void teardown_gl();

        void PushGL(GLObject *o);
        void PopGL();
        void ClearGL();
        
        void PushLight(GLLight *l);
        void PopLight();
        void ClearLights();
        
        void Render();

        Vertex& GetCamPos();
        Vertex& GetCamFocus();
        
        void wait_for_ready();
        
        void Resize();
};

}

#endif
