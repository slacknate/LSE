#include "gui/window/window.h"
#include "lse/engine.h"

/*
OpenGL version variables.
*/
static int glVersion = 0, slVersion = 0;
static char *glVersionString = NULL, *slVersionString = NULL;

/*
OpenGL implementation detail variables.
*/
static int glMaxVertexAttribs = 0;
static int glMaxColorAttach = 0;

/*
OpenGL version fetching function.
*/
const int LSE_GLVersion() {
    
    return ((const int)glVersion);
}

/*
OpenGL version fetching function.
*/
const char *const LSE_GLVersionString() {
    
    return ((const char *const)&glVersionString[0]);
}

/*
GLSL version fetching function.
*/
const int LSE_SLVersion() {
    
    return ((const int)slVersion);
}

/*
GLSL version fetching function.
*/
const char *const LSE_SLVersionString() {
    
    return ((const char *const)&slVersionString[0]);
}

/*
Fetch max number of vertex attributes.
*/
const int LSE_MaxGLVertAttrib() {
    
    return (const int)glMaxVertexAttribs;
}

/*
Fetch max number of frame buffer object color attachments.
*/
const int LSE_MaxFBOColorAttachments() {
    
    return (const int)glMaxColorAttach;
}

/*
Initialize our canvas.
We save the opengl clear bitmask,
as well as the canvas height, width,
and aspect ratio information.
*/
LSE_GLWindow_Base::LSE_GLWindow_Base(const char *const title, unsigned int m, int w, int h, double angle, double zi, double za) {
    
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
            
    up = LSE_Vector(0.0, 1.0, 0.0);
}

/*
Delete all objects.
*/
LSE_GLWindow_Base::~LSE_GLWindow_Base() {
    
    drawList.Clear();
    lightList.Clear();
    
    if(glVersionString != NULL)
        delete[] glVersionString;
        
    if(slVersionString != NULL)
        delete[] slVersionString;
        
    if(screen != NULL)
        delete screen;
        
    this->GLContextDestroy();
}

void LSE_GLWindow_Base::SetupIO(LSE_IOHandler *h) {
    
    this->handler = h;
}

/*
Initialize OpenGL and the Extension Wrangler.
Invoke this method after an
OpenGL context has been obtained.
(mention attributes and stuff)
*/
void LSE_GLWindow_Base::GLInit() {
    
    LSE_TRY()
    
    this->GLContextInit();
    
    int glewStatus = glewInit();
    if(glewStatus != GLEW_OK)
        LSE_THROW(LSE_GL_INIT_FAIL/*, (const char *)glewGetErrorString(glewStatus)*/);
          
    LSE_MESSG_LOG("GL_VERSION: %s\nGL_SHADING_LANGUAGE_VERSION: %s", LSE_GL_VENDOR_VERSION, LSE_SL_VENDOR_VERSION);
    
    // get the OpenGL version as an integer
    int glMajor = 0, glMinor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &glMajor);
    glGetIntegerv(GL_MINOR_VERSION, &glMinor);
    glVersion = (100*glMajor + 10*glMinor); 
    
    // get the GLSL version as an integer
    if(glVersion >= 330)
        slVersion = glVersion;
    else
        slVersion = glVersion - 170;   
    
    int numDots = 0;
    for(int i = 0; i < strlen(LSE_GL_VENDOR_VERSION); ++i) {
        
        if(LSE_GL_VENDOR_VERSION[i] == '.')
            ++numDots;
    }
    
    // get the OpenGL and GLSL versions as strings
    int length = strlen(LSE_GL_VENDOR_VERSION) - numDots + 1;
    glVersionString = new char [length];
    slVersionString = new char [length];
   
    memset(glVersionString, 0, length);
    memset(slVersionString, 0, length);
    
    int k = 0;
    for(int i = 0; i < strlen(LSE_GL_VENDOR_VERSION); ++i) {
        
        if(LSE_GL_VENDOR_VERSION[i] != '.') {
                
            glVersionString[k] = LSE_GL_VENDOR_VERSION[i];
            ++k;
        }
    }
        
    if(glVersion < 330) {
            
        slVersionString[0] = glVersionString[0] - 2;
        slVersionString[1] = glVersionString[1] + 3;
        slVersionString[2] = glVersionString[2];
    }
    else {
            
        strcpy(slVersionString, glVersionString);
    }
    
    // collect information about OpenGL
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &glMaxVertexAttribs);
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &glMaxColorAttach);
    // fix me -> fetch max number of uniforms
    
    int glStatus = LSE_GL_VERSION >= LSE_MIN_GL_VERSION && LSE_GL_MAX_VERT_ATTRIB >= LSE_GL_MIN_VERT_ATTRIB && LSE_GL_MAX_COLOR_ATTACH >= LSE_GL_MIN_COLOR_ATTACH;
    if(!glStatus)
        LSE_THROW(LSE_GL_INIT_FAIL/*, "OpenGL failed to meet certain requirements."*/);

    // compute and bind viewing matrix
    PlaceCamera();
    
    // compute and bind projection matrix
    AspectRatio();
    
    // create our framebuffer
    screen = new LSE_GLScreen(width, height);
    
    LSE_CATCH()
}

/*
Add an object to the graphics object list.
*/
void LSE_GLWindow_Base::PushGL(LSE_GLObject *o) {
    
    drawList.PushBack(o);
}

/*
Remove an object from the graphics object list.
*/
void LSE_GLWindow_Base::PopGL() {
    
    delete drawList.PopBack();
}

/*
Clear all graphics objects from the scene.
*/
void LSE_GLWindow_Base::ClearGL() {
    
    drawList.Clear();
}

/*
Add an object to the graphics object list.
*/
void LSE_GLWindow_Base::PushLight(LSE_GLLight *l) {
    
    lightList.PushBack(l);
}

/*
Remove an object from the graphics object list.
*/
void LSE_GLWindow_Base::PopLight() {
    
    delete lightList.PopBack();
}

/*
Clear all graphics objects from the scene.
*/
void LSE_GLWindow_Base::ClearLights() {
    
    lightList.Clear();
}

/*
Calculate the LSE_VIEW_MATRIX transformation matrix.

Reference:
    http://en.wikibooks.org/wiki/GLSL_Programming/Vertex_Transformations
*/
void LSE_GLWindow_Base::PlaceCamera() {
    
    LSE_Vector posVec(pos.x, pos.y, pos.z);
    
    LSE_Vector forward(focus.x - pos.x, focus.y - pos.y, focus.z - pos.z);
    forward.Normalize();
    forward = forward * -1.0;
    
    LSE_Vector side = forward % up;
    side.Normalize();
    
    up = forward % side;
    up.Normalize();
    
    LSE_VIEW_MATRIX[0] = side.I();
    LSE_VIEW_MATRIX[1] = up.I();
    LSE_VIEW_MATRIX[2] = forward.I();
    LSE_VIEW_MATRIX[3] = 0.0;
    
    LSE_VIEW_MATRIX[4] = side.J();
    LSE_VIEW_MATRIX[5] = up.J();
    LSE_VIEW_MATRIX[6] = forward.J();
    LSE_VIEW_MATRIX[7] = 0.0;
    
    LSE_VIEW_MATRIX[8] = side.K();
    LSE_VIEW_MATRIX[9] = up.K();
    LSE_VIEW_MATRIX[10] = forward.K();
    LSE_VIEW_MATRIX[11] = 0.0;
    
    LSE_VIEW_MATRIX[12] = -1.0 * (side * posVec);
    LSE_VIEW_MATRIX[13] = -1.0 * (up * posVec);
    LSE_VIEW_MATRIX[14] = -1.0 * (forward * posVec);
    LSE_VIEW_MATRIX[15] = 1.0;
}

/*
Calculate the aspect ratio transformation matrix.

Reference:
    http://en.wikibooks.org/wiki/GLSL_Programming/Vertex_Transformations
*/
void LSE_GLWindow_Base::AspectRatio() {
    
    double aspect = ((double)width/(double)height);
    double dz = zmin - zmax;
    
    if((dz == 0) || (sin(fovy * PI / 360.0) == 0) || (aspect == 0))
	   return;
	   
    double cotangent = 1.0 / tan(fovy * PI / 360.0);
    
    LSE_PROJ_MATRIX[0] = cotangent / aspect;
    LSE_PROJ_MATRIX[1] = 0.0;
    LSE_PROJ_MATRIX[2] = 0.0;
    LSE_PROJ_MATRIX[3] = 0.0; 
    LSE_PROJ_MATRIX[4] = 0.0;
    LSE_PROJ_MATRIX[5] = cotangent;
    LSE_PROJ_MATRIX[6] = 0.0;
    LSE_PROJ_MATRIX[7] = 0.0;
    LSE_PROJ_MATRIX[8] = 0.0;
    LSE_PROJ_MATRIX[9] = 0.0;
    LSE_PROJ_MATRIX[10] = (zmax + zmin) / dz;
    LSE_PROJ_MATRIX[11] = -1.0; 
    LSE_PROJ_MATRIX[12] = 0.0;
    LSE_PROJ_MATRIX[13] = 0.0;
    LSE_PROJ_MATRIX[14] = 2.0 * zmin * zmax / dz; 
    LSE_PROJ_MATRIX[15] = 0.0;
}

/*
Draw our objects on the canvas.
*/
void LSE_GLWindow_Base::Render() {    
    
    screen->BindFBO();
    
    glClear(mask);
    PlaceCamera();
    
    for(int i = 0; i < drawList.Size(); ++i) {
        
        LSE_GLObject *gl_object = (LSE_GLObject *)drawList[i]->GetData();
        //LSE_Quaternion q(1.0, 2.0, 3.0, 10.0*cos(PI/190.0));
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
LSE_Vertex& LSE_GLWindow_Base::GetCamPos() {
    
    return pos;
}

/*

*/
LSE_Vertex& LSE_GLWindow_Base::GetCamFocus() {
    
    return focus;
}

/*

*/
bool LSE_GLWindow_Base::Ready() {
    
    return initialized;
}

/*

*/
void LSE_GLWindow_Base::Resize() {
    
    screen->Resize(width, height);
    AspectRatio();
}

