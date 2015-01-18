#include "gl/manager.h"
using namespace LSE;

/*
OpenGL and Extension Wrangler includes.
*/
#include <gl/glew.h>
#include <gl/gl.h>

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
Get the OpenGL version as an integer.
*/
int init_gl_version() {

    int gl_version = 0;
    int gl_major = 0, gl_minor = 0;

    glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
    glGetIntegerv(GL_MINOR_VERSION, &gl_minor);

    gl_version = (100 * gl_major + 10 * gl_minor);

    return gl_version;
}

/*

*/
const char* init_gl_vendor_version() {

    return (const char *)glGetString(GL_VERSION);
}

/*
Get the GLSL version as an integer.
*/
int init_sl_version() {

    int sl_version = 0;

    const int gl_version = init_gl_version();

    // FIXME: use constants instead of magic numbers
    if(gl_version >= 330)
        sl_version = gl_version;

    else
        sl_version = gl_version - 170;

    return sl_version;
}

/*

*/
const char* init_sl_vendor_version() {

    return (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
}

/*
Fetch max number of vertex attributes.
*/
int init_max_vertex_attr() {

    int gl_max_vert_attr;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &gl_max_vert_attr);
    return gl_max_vert_attr;
}

/*
Fetch max number of frame buffer object color attachments.
*/
int init_max_fbo_attach() {

    int gl_max_color_attach;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &gl_max_color_attach);
    return gl_max_color_attach;
}

GLManager::GLManager() : max_vertex_attributes(init_max_vertex_attr()),
                         max_fbo_color_attachments(init_max_fbo_attach()),
                         gl_version(init_gl_version()), gl_vendor_version(init_gl_vendor_version()),
                         sl_version(init_sl_version()), sl_vendor_version(init_sl_vendor_version()) {}

/*

*/
const char* GLManager::error_string(GLenum e) {

    // FIXME: this is sketch. what if the GLEnum range changes?
    int err_index = gl_error - 0x0500;
    if(err_index >= 0 && err_index < 7)
        return GL_ERRORS[err_index];

    else
        return "Unknown OpenGL error.";
}