#include "gui/screen/screen.h"
#include "gui/screen/shaders.h"
using namespace LSE;

/*
Initialize our screen. Store the width
and height of our render surface,
allocate all memory needed, and create
our frame buffer object.
*/
LSE_GLScreen::LSE_GLScreen(int w, int h) {
    
    frameBufferID = renderBufferID = colorTexID = normalTexID = 0;
    
    program.AddShader(LSE_GetScreenShaders(SHADER_VERT), SHADER_VERT);
    program.AddShader(LSE_GetScreenShaders(SHADER_FRAG), SHADER_FRAG);
        
    if(!program.Finalize())
        throw LSE_Exception(__FILE__, __LINE__, LSE_GL_INIT_FAIL/*, LSE_ErrorString(LSE_GL_PROG_FAIL)*/);
        
    program.BindUniform(LSE_IN1, "FRAG_TEXTURE", 0);
    
    vertices = new double [3*this->SCREEN_VERT_COUNT];
    indices = new int [3*this->SCREEN_ELEM_COUNT];
    texCoords = new int [2*this->SCREEN_VERT_COUNT];
    
    CalcVertices();
    CalcIndices();
    CalcTexCoords();
    
    Resize(w, h);
}

/*
Free all memory and OpenGL objects.
*/
LSE_GLScreen::~LSE_GLScreen() {
    
    glDeleteTextures(1, &normalTexID);    
    glDeleteTextures(1, &colorTexID);
    glDeleteRenderbuffers(1, &renderBufferID);
    glDeleteFramebuffers(1, &frameBufferID);
}

/*
Predefined quad vertices.
*/
void LSE_GLScreen::CalcVertices() {
    
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
void LSE_GLScreen::CalcIndices() {
    
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
}

/*

*/
void LSE_GLScreen::CalcTexCoords() {
    
    // v0
    texCoords[0] = 0;
    texCoords[1] = 0;
    
    // v1
    texCoords[2] = 1;
    texCoords[3] = 0;
    
    // v2
    texCoords[4] = 1;
    texCoords[5] = 1;
    
    // v3
    texCoords[6] = 0;
    texCoords[7] = 1;
}

/*
Create a new framebuffer object with a new width
and height.
*/
void LSE_GLScreen::Resize(int w, int h) {
    
    width = w;
    height = h;
    
    glViewport(0, 0, width, height);
    
    if(frameBufferID != 0)
        glDeleteFramebuffers(1, &frameBufferID);
        
    if(renderBufferID != 0)
        glDeleteRenderbuffers(1, &renderBufferID);
        
    if(colorTexID != 0)
        glDeleteTextures(1, &colorTexID);
        
    if(normalTexID != 0)
        glDeleteTextures(1, &normalTexID);
    
    glGenFramebuffers(1, &frameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
    
    glGenRenderbuffers(1, &renderBufferID);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);
    
    glGenTextures(1, &colorTexID);
    glBindTexture(GL_TEXTURE_2D, colorTexID);
    // fix me -> need proper texture parameters?
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glGenTextures(1, &normalTexID);
    glBindTexture(GL_TEXTURE_2D, normalTexID);
    // fix me -> need proper texture parameters?
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexID, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normalTexID, 0);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBufferID);
    
    GLenum DrawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, DrawBuffers);
    
    fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(fboStatus != GL_FRAMEBUFFER_COMPLETE)
        LOG(LOG_LEVEL_ERROR, "Frame buffer object creation failed.");
    
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/*
Bind to our frame buffer.
*/
void LSE_GLScreen::BindFBO() {
    
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
}

/*
Unbind from our framebuffer.
*/
void LSE_GLScreen::UnbindFBO() {
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/*
Render the contents of our framebuffer.
*/
void LSE_GLScreen::Render() {
    
    glBindTexture(GL_TEXTURE_2D, colorTexID);
    glActiveTexture(GL_TEXTURE0);
    
    program.Bind();
    
    glEnableVertexAttribArray(VERT_POSITION);
    glEnableVertexAttribArray(VERT_TEX_COORD);
        
    glVertexAttribPointer(VERT_POSITION, 3, GL_DOUBLE, GL_FALSE, 0, vertices);
    glVertexAttribPointer(VERT_TEX_COORD, 2, GL_INT, GL_FALSE, 0, texCoords);
        
    glDrawElements(GL_TRIANGLES, 3*this->SCREEN_ELEM_COUNT, GL_UNSIGNED_INT, indices);
        
    glDisableVertexAttribArray(VERT_TEX_COORD);
    glDisableVertexAttribArray(VERT_POSITION);
    
    program.Unbind();
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

/*

*/
bool LSE_GLScreen::FBOActive() {
    
    return fboStatus;
}
