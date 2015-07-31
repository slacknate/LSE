#include "gui/screen/screen.h"
#include "gui/screen/shaders.h"
#include "lse/globals.h"
#include "lse/exception.h"
using namespace LSE;

/*
Initialize our screen. Store the width
and height of our render surface,
allocate all memory needed, and create
our frame buffer object.
*/
GLScreen::GLScreen(int w, int h) {
    
    frame_buffer_id = render_buffer_id = color_tex_id = normal_tex_id = 0;
    
    program.AddShader(GetScreenShaders(SHADER_VERT), SHADER_VERT);
    program.AddShader(GetScreenShaders(SHADER_FRAG), SHADER_FRAG);
        
    if(!program.Finalize())
        throw EXCEPTION("OpenGL failed to initialize");
        
    program.BindUniform(IN1, "FRAG_TEXTURE", 0);
    
    vertices = new double [3*this->SCREEN_VERT_COUNT];
    indices = new int [3*this->SCREEN_ELEM_COUNT];
    tex_coords = new int [2*this->SCREEN_VERT_COUNT];

    calc_vertices();
    calc_indices();
    calc_tex_coords();
    
    resize(w, h);
}

/*
Free all memory and OpenGL objects.
*/
GLScreen::~GLScreen() {
    
    glDeleteTextures(1, &normal_tex_id);
    glDeleteTextures(1, &color_tex_id);
    glDeleteRenderbuffers(1, &render_buffer_id);
    glDeleteFramebuffers(1, &frame_buffer_id);
}

/*
Predefined quad vertices.
*/
void GLScreen::calc_vertices() {
    
    // v0
    vertices[0] = -1.0/2.0;
    vertices[1] = -1.0/2.0;
    vertices[2] = 0.0;
    
    // v1
    vertices[3] = 1.0/2.0;
    vertices[4] = -1.0/2.0;
    vertices[5] = 0.0;
    
    // v2
    vertices[6] = 1.0/2.0;
    vertices[7] = 1.0/2.0;
    vertices[8] = 0.0;
    
    // v3
    vertices[9] = -1.0/2.0;
    vertices[10] = 1.0/2.0;
    vertices[11] = 0.0;
}

/*
Tell OpenGL which vertices to use,
and where.
*/
void GLScreen::calc_indices() {
    
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
}

/*

*/
void GLScreen::calc_tex_coords() {
    
    // v0
    tex_coords[0] = 0;
    tex_coords[1] = 0;
    
    // v1
    tex_coords[2] = 1;
    tex_coords[3] = 0;
    
    // v2
    tex_coords[4] = 1;
    tex_coords[5] = 1;
    
    // v3
    tex_coords[6] = 0;
    tex_coords[7] = 1;
}

/*
Create a new framebuffer object with a new width
and height.
*/
void GLScreen::resize(int w, int h) {
    
    width = w;
    height = h;
    
    glViewport(0, 0, width, height);
    
    if(frame_buffer_id != 0)
        glDeleteFramebuffers(1, &frame_buffer_id);
        
    if(render_buffer_id != 0)
        glDeleteRenderbuffers(1, &render_buffer_id);
        
    if(color_tex_id != 0)
        glDeleteTextures(1, &color_tex_id);
        
    if(normal_tex_id != 0)
        glDeleteTextures(1, &normal_tex_id);
    
    glGenFramebuffers(1, &frame_buffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_id);
    
    glGenRenderbuffers(1, &render_buffer_id);
    glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_id);
    
    glGenTextures(1, &color_tex_id);
    glBindTexture(GL_TEXTURE_2D, color_tex_id);
    // fix me -> need proper texture parameters?
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glGenTextures(1, &normal_tex_id);
    glBindTexture(GL_TEXTURE_2D, normal_tex_id);
    // fix me -> need proper texture parameters?
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_tex_id, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normal_tex_id, 0);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, render_buffer_id);
    
    GLenum DrawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, DrawBuffers);
    
    fbo_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(fbo_status != GL_FRAMEBUFFER_COMPLETE)
        logger.error("Frame buffer object creation failed.");
    
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/*
Bind to our frame buffer.
*/
void GLScreen::bind_fbo() {
    
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_id);
}

/*
Unbind from our framebuffer.
*/
void GLScreen::unbind_fbo() {
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/*
Render the contents of our framebuffer.
*/
void GLScreen::render() {
    
    glBindTexture(GL_TEXTURE_2D, color_tex_id);
    glActiveTexture(GL_TEXTURE0);
    
    program.Bind();
    
    glEnableVertexAttribArray(VERT_POSITION);
    glEnableVertexAttribArray(VERT_TEX_COORD);
        
    glVertexAttribPointer(VERT_POSITION, 3, GL_DOUBLE, GL_FALSE, 0, vertices);
    glVertexAttribPointer(VERT_TEX_COORD, 2, GL_INT, GL_FALSE, 0, tex_coords);
        
    glDrawElements(GL_TRIANGLES, 3*this->SCREEN_ELEM_COUNT, GL_UNSIGNED_INT, indices);
        
    glDisableVertexAttribArray(VERT_TEX_COORD);
    glDisableVertexAttribArray(VERT_POSITION);
    
    program.Unbind();
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

/*

*/
bool GLScreen::fbo_active() {
    
    return fbo_status;
}
