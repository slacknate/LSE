#ifndef LSE_GL_MAN_H
#define LSE_GL_MAN_H

#include <map>

namespace LSE {

typedef std::map<GLenum, const char *const> GLErrorMap;

/*
Minimum OpenGL and GLSL requirements.
*/
const int MIN_GL_VERSION = 320;
const int MIN_SL_VERSION = 150;
const int GL_MIN_COLOR_ATTACH = 2;
const int GL_MIN_VERT_ATTRIB = 6;


class GLManager {

    public:

        const int gl_version;
        const char *gl_vendor_version;

        const int sl_version;
        const char *sl_vendor_version;

        const int max_vertex_attributes;
        const int max_fbo_color_attachments;

        GLManager();

        const char *error_string(GLenum e);
};

}

#endif