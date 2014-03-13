#include "lse.h"
#include "prism.h"
#include "cam.h"

// engine name -> Lucent Shards Engine

/*
Initialize our scene.
*/
void CreateScene(LSE_GLWindow *window) {
    
    TestPrism *prism = new TestPrism(window, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    window->PushGL(prism);
    
    //LSE_GLLight *light = new LSE_GLLight();
    //window->PushLight(light);
}

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
    
    LSE_Engine engine(GLInit, CreateScene);
    
    int mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
    engine.InitWindow("Engine", mask, 640, 480, 90.0, 1.0, 20.0); 
    
    return engine.Run();
}
