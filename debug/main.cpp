#include "lse.h"
#include "prism.h"
#include "cam.h"
using namespace LSE;


/*
Program entry point.
Create an OpenGL context and a scene to
render. Run the engine.
*/
int main(int argc, char *argv[]) {
    
    Engine engine(argc, argv);
    
    unsigned int mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
    GLWindow *window = new GLWindow("Engine", mask, 640, 480, 90.0, 1.0, 20.0);
    engine.attach_window(window);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    return engine.run();
}
