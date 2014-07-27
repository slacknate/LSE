#include "lse.h"
#include "prism.h"
#include "cam.h"
using namespace LSE;

/*
Initialize our scene.
*/
void InitScene(GLWindow *window) {
    
    TestPrism *prism = new TestPrism(window, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    window->PushGL(prism);
    
    //GLLight *light = new GLLight();
    //window->PushLight(light);
}

/*
Initialize our OpenGL settings.
*/
void GLInit() {
    
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

/*
Program entry point.
Create an OpenGL context and a scene to
render. Run the engine.
*/
int main(int argc, char *argv[]) {
    
    Engine engine(argc, argv);
    
    int mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
    engine.InitWindow("Engine", mask, 640, 480, 90.0, 1.0, 20.0);
    
    return engine.Run();
}
