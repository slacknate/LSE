#include "lse.h"
#include "prism.h"
#include "cam.h"
using namespace LSE;


/*
 * GLWindow ready callback function.
 */
void ready_func(GLWindow *window) {

    TestPrism *prism1 = new TestPrism(window, -1.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    window->push_gl(prism1);

    TestPrism *prism2 = new TestPrism(window, 1.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    window->push_gl(prism2);
}


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

    return engine.run(ready_func);
}
