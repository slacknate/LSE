#include "lse/defs.h"
#if defined(_WIN32) || defined(_WIN64) // all windows variants
#include <windows.h>
#elif defined(__unix__) && !defined(__APPLE__) // all unix variants, non-mac
// put nix include here
#elif defined(__APPLE__) && !defined(__MACH__) // mac osx, non-ios
// put mac include here
#endif
using namespace LSE;

/*
OpenGL error messages.
*/
static const char *const GL_ERRORS[] = {
    
    "GL_INVALID_ENUM",
    "GL_INVALID_VALUE",
    "GL_INVALID_OPERATION",
    "GL_INVALID_FRAMEBUFFER_OPERATION",
    "GL_OUT_OF_MEMORY",
    "GL_STACK_UNDERFLOW",
    "GL_STACK_OVERFLOW"
};

/*

*/
static const char *const STATUS_ID_STRINGS[] = {
    
    "OK",
    "GL_INIT_FAIL",
    "GL_PROG_FAIL",
    "BAD_ALLOC",
    "BAD_CAST",
    "BAD_EXCEPTION",
    "BAD_TYPE_ID",
    "IOS_FAIL",
    "RUNTIME_ERR",
    "LOGIC_ERR",
    "WIN_REG_FAIL",
    "WIN_CREATE_FAIL",
    "GL_CON_FAIL",
    "IO_SETUP_FAIL",
    "STAT_LAST"
};

/*
LSE Status strings.
*/
static const char *const STATUS_STRINGS[] = {
    
    "No errors. ",
    "OpenGL failed to initialize. ",
    "OpenGL shader program failed to verify. ",
    "Bad memory allocation. ",
    "Bad dynamic cast. ",
    "Unhandled exceptions. ",
    "NULL pointer passed to typeid(). ",
    "Stream error. ",
    "Logic error. ",
    "Runtime error. ",
    "Failed to register window. ",
    "Failed to create window. ",
    "Failed to obtain an OpenGL context. ",
    "Failed to setup IO handlers. ",
    "Unknown error code. "
};

namespace LSE {

/*
LSE Error status.
*/
static int error_status = OK;

/*
Return the string equivalent of an
OpenGL error code.
*/
const char* GLErrorString(GLenum gl_error) {
    
    int err_index = gl_error - 0x0500;
    if(err_index >= 0 && err_index < 7)
        return GL_ERRORS[err_index];
        
    else
        return "Unknown OpenGL error.";
}

/*

*/
int StatusCode(int code) {
    
    if(code >= OK && code < STAT_LAST)
        error_status = code;
        
    return error_status;
}

/*
Platform specific error code fetcher.

TODO: make this less sloochy?
*/
int ExtendedStatusCode() {
#if defined(_WIN32) || defined(_WIN64) // all windows variants
    return GetLastError();
#elif defined(__unix__) && !defined(__APPLE__) // all unix variants, non-mac
    return 0; // FIXME
#elif defined(__APPLE__) && !defined(__MACH__) // mac osx, non-ios
    return 0; // FIXME
#endif
}

/*

*/
const char* StatusString(int code) {
    
    if(code >= OK && code < STAT_LAST)
        return STATUS_STRINGS[code];
        
    else
        return STATUS_STRINGS[error_status];
}

/*

*/
const char* StatusID(int code) {
    
    if(code >= OK && code < STAT_LAST)
        return STATUS_ID_STRINGS[code];
        
    else
        return STATUS_ID_STRINGS[error_status];
}

/*
Get the OpenGL version as an integer.
*/
int GLVersion() {
    
    static int gl_version = 0;
    
    if(gl_version == 0) {
    
        int gl_major = 0, gl_minor = 0;
        
        glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
        glGetIntegerv(GL_MINOR_VERSION, &gl_minor);
        
        gl_version = (100 * gl_major + 10 * gl_minor); 
    }
    
    return gl_version;
}

/*
Get the GLSL version as an integer.
*/
int SLVersion() {
    
    static int sl_version = 0;
    
    if(sl_version == 0) {
        
        const int gl_version = GLVersion();
    
        if(gl_version >= 330)
            sl_version = gl_version;
            
        else
            sl_version = gl_version - 170;   
    }
    
    return sl_version;
}

/*
Fetch max number of vertex attributes.
*/
int MaxGLVertAttrib() {
    
    int gl_max_vert_attr;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &gl_max_vert_attr);
    return gl_max_vert_attr;
}

/*
Fetch max number of frame buffer object color attachments.
*/
int MaxFBOColorAttachments() {
    
    int gl_max_color_attach;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &gl_max_color_attach);
    return gl_max_color_attach;
}

/*

*/
const char* GLVendorVersion() {
    
    return (const char *)glGetString(GL_VERSION);
}

/*

*/
const char* SLVendorVersion() {
    
    return (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
}

// fix me -> fetch max number of uniforms

}
