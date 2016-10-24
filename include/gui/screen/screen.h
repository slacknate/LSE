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
        
        GLProgram program; //
        float *vertices; //
        int *tex_coords; //
        int *indices; //
        
        int width, height; // screen size parameters
        int fbo_status; // status of framebuffer object creation
        unsigned int frame_buffer_id, render_buffer_id, color_tex_id, normal_tex_id; // OpenGL IDs
        
        void calc_vertices();
        void calc_indices();
        void calc_tex_coords();
    
    public:
        
        GLScreen(int new_width, int new_height);
        ~GLScreen();
        
        void resize(int new_width, int new_height);
        
        void bind_fbo();
        void unbind_fbo();
        
        void render();
        
        bool fbo_active();
};

}

#endif
