#ifndef LSE_GL_SCREEN_H
#define LSE_GL_SCREEN_H

#include "gl/program.h"

namespace LSE {

/*
Representation of an OpenGL frambuffer.
This is essentially a specialized
GLPrimitive.
*/
class GLScreen {
    
    private:
        
        static const int SCREEN_VERT_COUNT = 4;
        static const int SCREEN_ELEM_COUNT = 2;
        
        GLProgram program; //
        double *vertices; //
        int *tex_coords; //
        int *indices; //
        
        int width, height; // screen size parameters
        int fbo_status; // status of framebuffer object creation
        unsigned int frame_buffer_id, render_buffer_id, color_tex_id, normal_tex_id; // OpenGL IDs
        
        void calc_vertices();
        void calc_indices();
        void calc_tex_coords();
    
    public:
        
        GLScreen(int w, int h);
        ~GLScreen();
        
        void resize(int w, int h);
        
        void bind_fbo();
        void unbind_fbo();
        
        void render();
        
        bool fbo_active();
};

}

#endif
