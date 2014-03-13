#ifndef LSE_GL_SCREEN_H
#define LSE_GL_SCREEN_H

#include "gl/program.h"

#define SCREEN_VERT_COUNT 4
#define SCREEN_ELEM_COUNT 2

/*
Representation of an OpenGL frambuffer.
This is essentially a specialized
LSE_GLPrimitive.
*/
class LSE_GLScreen {
    
    private:
        
        LSE_GLProgram program; //
        double *vertices; //
        int *texCoords; //
        int *indices; //
        
        int width, height; // screen size parameters
        int fboStatus; // status of framebuffer object creation
        unsigned int frameBufferID, renderBufferID, colorTexID, normalTexID; // OpenGL IDs
        
        void CalcVertices();
        void CalcIndices();
        void CalcTexCoords();
    
    public:
        
        LSE_GLScreen(int w, int h);
        ~LSE_GLScreen();
        
        void Resize(int w, int h);
        
        void BindFBO();
        void UnbindFBO();
        
        void Render();
        
        bool FBOActive();
};

#endif
