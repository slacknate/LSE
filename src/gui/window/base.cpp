#include "gui/window/window.h"
#include "lse/engine.h"
using namespace LSE;

/*
Initialize our canvas.
We save the opengl clear bitmask,
as well as the canvas height, width,
and aspect ratio information.
*/
GLWindow_Base::GLWindow_Base(const char *const title, unsigned int m, int w, int h, double angle, double zi, double za) {
    
    initialized = false;
    mask = m;
    windowTitle = title;
    width = w;
    height = h;
    fovy = angle;
    zmin = zi;
    zmax = za;
    
    pos.x = 0.0;
    pos.y = 0.0;
    pos.z = 1.0;
            
    focus.x = 0.0;
    focus.y = 0.0;
    focus.z = 0.0;
            
    up = Vector(0.0, 1.0, 0.0);
}

/*
Delete all objects.
*/
GLWindow_Base::~GLWindow_Base() {
    
    drawList.Clear();
    lightList.Clear();
        
    if(screen != NULL)
        delete screen;
        
    this->GLContextDestroy();
}

void GLWindow_Base::SetupIO(IOHandler *h) {
    
    this->handler = h;
}

/*
Initialize OpenGL and the Extension Wrangler.
Invoke this method after an
OpenGL context has been obtained.
(mention attributes and stuff)
*/
void GLWindow_Base::GLInit() {
    
    try {
    
    this->GLContextInit();
    
    int glewStatus = glewInit();
    if(glewStatus != GLEW_OK)
        throw Exception(__FILE__, __LINE__, GL_INIT_FAIL/*, (const char *)glewGetErrorString(glewStatus)*/);
    
    LOG(LOG_LEVEL_INFO, "GL_VERSION: %s\nGL_SHADING_LANGUAGE_VERSION: %s", GLVendorVersion(), SLVendorVersion());
        
    int glStatus = GLVersion() >= MIN_GL_VERSION && MaxGLVertAttrib() >= GL_MIN_VERT_ATTRIB && MaxFBOColorAttachments() >= GL_MIN_COLOR_ATTACH;
    if(!glStatus)
        throw Exception(__FILE__, __LINE__, GL_INIT_FAIL);

    // compute and bind viewing matrix
    PlaceCamera();
    
    // compute and bind projection matrix
    AspectRatio();
    
    // create our framebuffer
    screen = new GLScreen(width, height);
        
    }
    catch(std::exception &e) {
        
        throw Exception(__FILE__, __LINE__, OK); // FIXME: need a way to "convert" standard exceptions into LSE exceptions
    }
}

/*
Add an object to the graphics object list.
*/
void GLWindow_Base::PushGL(GLObject *o) {
    
    drawList.PushBack(o);
}

/*
Remove an object from the graphics object list.
*/
void GLWindow_Base::PopGL() {
    
    delete drawList.PopBack();
}

/*
Clear all graphics objects from the scene.
*/
void GLWindow_Base::ClearGL() {
    
    drawList.Clear();
}

/*
Add an object to the graphics object list.
*/
void GLWindow_Base::PushLight(GLLight *l) {
    
    lightList.PushBack(l);
}

/*
Remove an object from the graphics object list.
*/
void GLWindow_Base::PopLight() {
    
    delete lightList.PopBack();
}

/*
Clear all graphics objects from the scene.
*/
void GLWindow_Base::ClearLights() {
    
    lightList.Clear();
}

/*
Calculate the VIEW_MATRIX transformation matrix.

Reference:
    http://en.wikibooks.org/wiki/GLSL_Programming/Vertex_Transformations
*/
void GLWindow_Base::PlaceCamera() {
    
    Vector posVec(pos.x, pos.y, pos.z);
    
    Vector forward(focus.x - pos.x, focus.y - pos.y, focus.z - pos.z);
    forward.Normalize();
    forward = forward * -1.0;
    
    Vector side = forward % up;
    side.Normalize();
    
    up = forward % side;
    up.Normalize();
    
    VIEW_MATRIX[0] = side.I();
    VIEW_MATRIX[1] = up.I();
    VIEW_MATRIX[2] = forward.I();
    VIEW_MATRIX[3] = 0.0;
    
    VIEW_MATRIX[4] = side.J();
    VIEW_MATRIX[5] = up.J();
    VIEW_MATRIX[6] = forward.J();
    VIEW_MATRIX[7] = 0.0;
    
    VIEW_MATRIX[8] = side.K();
    VIEW_MATRIX[9] = up.K();
    VIEW_MATRIX[10] = forward.K();
    VIEW_MATRIX[11] = 0.0;
    
    VIEW_MATRIX[12] = -1.0 * (side * posVec);
    VIEW_MATRIX[13] = -1.0 * (up * posVec);
    VIEW_MATRIX[14] = -1.0 * (forward * posVec);
    VIEW_MATRIX[15] = 1.0;
}

/*
Calculate the aspect ratio transformation matrix.

Reference:
    http://en.wikibooks.org/wiki/GLSL_Programming/Vertex_Transformations
*/
void GLWindow_Base::AspectRatio() {
    
    double aspect = ((double)width/(double)height);
    double dz = zmin - zmax;
    
    if((dz == 0) || (sin(fovy * PI / 360.0) == 0) || (aspect == 0))
	   return;
	   
    double cotangent = 1.0 / tan(fovy * PI / 360.0);
    
    PROJ_MATRIX[0] = cotangent / aspect;
    PROJ_MATRIX[1] = 0.0;
    PROJ_MATRIX[2] = 0.0;
    PROJ_MATRIX[3] = 0.0; 
    PROJ_MATRIX[4] = 0.0;
    PROJ_MATRIX[5] = cotangent;
    PROJ_MATRIX[6] = 0.0;
    PROJ_MATRIX[7] = 0.0;
    PROJ_MATRIX[8] = 0.0;
    PROJ_MATRIX[9] = 0.0;
    PROJ_MATRIX[10] = (zmax + zmin) / dz;
    PROJ_MATRIX[11] = -1.0; 
    PROJ_MATRIX[12] = 0.0;
    PROJ_MATRIX[13] = 0.0;
    PROJ_MATRIX[14] = 2.0 * zmin * zmax / dz; 
    PROJ_MATRIX[15] = 0.0;
}

/*
Draw our objects on the canvas.
*/
void GLWindow_Base::Render() {    
    
    screen->BindFBO();
    
    glClear(mask);
    PlaceCamera();
    
    for(int i = 0; i < drawList.Size(); ++i) {
        
        GLObject *gl_object = (GLObject *)drawList[i]->GetData();
        //Quaternion q(1.0, 2.0, 3.0, 10.0*cos(PI/190.0));
        //gl_object->Transform(q);
        gl_object->Render();
        
        if(1 == 2) // fix me -> real condition
            gl_object->RenderNormals();
    }
    
    screen->UnbindFBO();
    
    glClear(mask);
    
    screen->Render();
    
    this->SwapGLBuffers();
}

/*

*/
Vertex& GLWindow_Base::GetCamPos() {
    
    return pos;
}

/*

*/
Vertex& GLWindow_Base::GetCamFocus() {
    
    return focus;
}

/*

*/
bool GLWindow_Base::Ready() {
    
    return initialized;
}

/*

*/
void GLWindow_Base::Resize() {
    
    screen->Resize(width, height);
    AspectRatio();
}

