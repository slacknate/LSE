#include "gui/screen/screen.h"
/*
 * The following two headers are
 * auto-generated at build time.
 */
#include "gui/screen/fragshader.h"
#include "gui/screen/vertshader.h"
#include "lse/globals.h"
#include "lse/exception.h"
using namespace LSE;

static const int SCREEN_VERT_COUNT = 4;
static const int SCREEN_ELEM_COUNT = 2;

/*
Initialize our screen. Store the width
and height of our render surface,
allocate all memory needed, and create
our frame buffer object.
*/
GLScreen::GLScreen(int new_width, int new_height) : frame_buffer_id(0), render_buffer_id(0), color_tex_id(0), normal_tex_id(0) {

    this->program.add_shader(VERT_SHADER, SHADER_VERT);
    this->program.add_shader(FRAG_SHADER, SHADER_FRAG);
        
    if(!this->program.finalize())
        throw EXCEPTION("OpenGL failed to initialize");

    this->program.uniform(IN1, "FRAG_TEXTURE", 0);

    this->vertices = new float [3*SCREEN_VERT_COUNT];
    this->indices = new int [3*SCREEN_ELEM_COUNT];
    this->tex_coords = new int [2*SCREEN_VERT_COUNT];

    this->calc_vertices();
    this->calc_indices();
    this->calc_tex_coords();

    this->resize(new_width, new_height);
}

/*
Free all memory and OpenGL objects.
*/
GLScreen::~GLScreen() {
    
    glDeleteTextures(1, &this->normal_tex_id);
    glDeleteTextures(1, &this->color_tex_id);
    glDeleteRenderbuffers(1, &this->render_buffer_id);
    glDeleteFramebuffers(1, &this->frame_buffer_id);
}

/*
Predefined quad vertices.
*/
void GLScreen::calc_vertices() {
    
    // v0
    this->vertices[0] = -1.0/2.0;
    this->vertices[1] = -1.0/2.0;
    this->vertices[2] = 0.0;
    
    // v1
    this->vertices[3] = 1.0/2.0;
    this->vertices[4] = -1.0/2.0;
    this->vertices[5] = 0.0;
    
    // v2
    this->vertices[6] = 1.0/2.0;
    this->vertices[7] = 1.0/2.0;
    this->vertices[8] = 0.0;
    
    // v3
    this->vertices[9] = -1.0/2.0;
    this->vertices[10] = 1.0/2.0;
    this->vertices[11] = 0.0;
}

/*
Tell OpenGL which vertices to use,
and where.
*/
void GLScreen::calc_indices() {

    this->indices[0] = 0;
    this->indices[1] = 1;
    this->indices[2] = 2;
    this->indices[3] = 0;
    this->indices[4] = 2;
    this->indices[5] = 3;
}

/*

*/
void GLScreen::calc_tex_coords() {
    
    // v0
    this->tex_coords[0] = 0;
    this->tex_coords[1] = 0;
    
    // v1
    this->tex_coords[2] = 1;
    this->tex_coords[3] = 0;
    
    // v2
    this->tex_coords[4] = 1;
    this->tex_coords[5] = 1;
    
    // v3
    this->tex_coords[6] = 0;
    this->tex_coords[7] = 1;
}

/*
Create a new framebuffer object with a new width
and height.
*/
void GLScreen::resize(int new_width, int new_height) {

    this->width = new_width;
    this->height = new_height;
    
    glViewport(0, 0, this->width, this->height);
    
    if(this->frame_buffer_id != 0)
        glDeleteFramebuffers(1, &this->frame_buffer_id);
        
    if(this->render_buffer_id != 0)
        glDeleteRenderbuffers(1, &this->render_buffer_id);
        
    if(this->color_tex_id != 0)
        glDeleteTextures(1, &this->color_tex_id);
        
    if(this->normal_tex_id != 0)
        glDeleteTextures(1, &this->normal_tex_id);
    
    glGenFramebuffers(1, &this->frame_buffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer_id);
    
    glGenRenderbuffers(1, &this->render_buffer_id);
    glBindRenderbuffer(GL_RENDERBUFFER, this->render_buffer_id);
    
    glGenTextures(1, &this->color_tex_id);
    glBindTexture(GL_TEXTURE_2D, this->color_tex_id);
    // fix me -> need proper texture parameters?
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glGenTextures(1, &this->normal_tex_id);
    glBindTexture(GL_TEXTURE_2D, this->normal_tex_id);
    // fix me -> need proper texture parameters?
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->color_tex_id, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, this->normal_tex_id, 0);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->width, this->height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->render_buffer_id);
    
    GLenum DrawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, DrawBuffers);

    this->fbo_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(this->fbo_status != GL_FRAMEBUFFER_COMPLETE)
        logger.error("Frame buffer object creation failed.");
    
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/*
bind to our frame buffer.
*/
void GLScreen::bind_fbo() {
    
    glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer_id);
}

/*
unbind from our framebuffer.
*/
void GLScreen::unbind_fbo() {
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/*
Render the contents of our framebuffer.
*/
void GLScreen::render() {
    
    glBindTexture(GL_TEXTURE_2D, this->color_tex_id);
    glActiveTexture(GL_TEXTURE0);

    this->program.bind();
    
    glEnableVertexAttribArray(VERT_POSITION);
    glEnableVertexAttribArray(VERT_TEX_COORD);
        
    glVertexAttribPointer(VERT_POSITION, 3, GL_FLOAT, GL_FALSE, 0, this->vertices);
    glVertexAttribPointer(VERT_TEX_COORD, 2, GL_INT, GL_FALSE, 0, this->tex_coords);
        
    glDrawElements(GL_TRIANGLES, 3*SCREEN_ELEM_COUNT, GL_UNSIGNED_INT, this->indices);
        
    glDisableVertexAttribArray(VERT_TEX_COORD);
    glDisableVertexAttribArray(VERT_POSITION);

    this->program.unbind();
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

/*

*/
bool GLScreen::fbo_active() {
    
    return (bool)this->fbo_status;
}
