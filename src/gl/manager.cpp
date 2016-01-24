#include "gl/manager.h"

namespace LSE {


/*
OpenGL error messages.
*/
// TODO: other error constants?
static const GLErrorMap GL_ERROR_MAP = GLErrorMap({

    {GL_INVALID_ENUM, "GL_INVALID_ENUM"},
    {GL_INVALID_VALUE, "GL_INVALID_VALUE"},
    {GL_INVALID_OPERATION, "GL_INVALID_OPERATION"},
    {GL_INVALID_FRAMEBUFFER_OPERATION, "GL_INVALID_FRAMEBUFFER_OPERATION"},
    {GL_OUT_OF_MEMORY, "GL_OUT_OF_MEMORY"},
    {GL_STACK_UNDERFLOW, "GL_STACK_UNDERFLOW"},
    {GL_STACK_OVERFLOW, "GL_STACK_OVERFLOW"},
});

/*
Get the OpenGL version as an integer.
*/
int gl_version() {

    static int _gl_version = -1;

    if(_gl_version == -1) {

        int gl_major = 0, gl_minor = 0;

        glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
        glGetIntegerv(GL_MINOR_VERSION, &gl_minor);

        _gl_version = (100 * gl_major + 10 * gl_minor);
    }

    return _gl_version;
}

/*

*/
const char* gl_vendor_version() {

    static char *_gl_vendor_version = nullptr;

    if(_gl_vendor_version == nullptr)
        _gl_vendor_version = (char *)glGetString(GL_VERSION);

    return (const char *)_gl_vendor_version;
}

/*
Get the GLSL version as an integer.
*/
int sl_version() {

    static int _sl_version = -1;

    if(_sl_version == -1) {

        const int _gl_version = gl_version();

        // FIXME: use constants instead of magic numbers
        if(_gl_version >= 330)
            _sl_version = _gl_version;

        else
            _sl_version = _gl_version - 170;
    }

    return _sl_version;
}

/*

*/
const char* sl_vendor_version() {

    static char *_sl_vendor_version = nullptr;

    if(_sl_vendor_version == nullptr)
        _sl_vendor_version = (char *)glGetString(GL_SHADING_LANGUAGE_VERSION);

    return (const char *)_sl_vendor_version;
}

/*
Fetch max number of vertex attributes.
*/
int max_vertex_attr() {

    static int _max_vert_attr = -1;

    if(_max_vert_attr == -1)
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_max_vert_attr);

    return _max_vert_attr;
}

/*
Fetch max number of frame buffer object color attachments.
*/
int max_color_attach() {

    static int _max_color_attach = -1;

    if(_max_color_attach == -1)
        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &_max_color_attach);

    return _max_color_attach;
}

// FIXME: fetch max number of uniforms

/*

*/
const char* gl_error() {

    const GLenum err_code = glGetError();

    GLErrorMap::const_iterator error_it = GL_ERROR_MAP.find(err_code);

    // FIXME: don't use multiple return statements
    if(error_it == GL_ERROR_MAP.end())
        return "Unknown OpenGL error.";

    else
        return error_it->second;
}

}
