#ifndef LSE_GL_OBJ_H
#define LSE_GL_OBJ_H

#include "phy/object.h"
#include "gl/program.h"
#include "gl/material.h"

namespace LSE {

/*
Base class for all objects which are drawable
on an OpenGL canvas.
*/
class GLObject : public PHObject {
    
    protected:
        
        GLProgram program; // shader program
        Quaternion rotation; // object orientation
        float translation[16];

        virtual void CalcNormals() {} // calculate normal vectors to all surfaces

        void init_translation_matrix();
        
    public:
        
        GLObject(float x, float y, float z);
        
        GLProgram* GetProgram();
        
        void translate(Vector& v);
        void rotate(Quaternion& q);
        
        void Render();
        
        virtual void Draw() {} // object specific render method
        virtual void RenderNormals() {} // object specific normal render method
        virtual bool Hit(float, float, float) { return false; } // collision detection method
        virtual Vector GetNormalAt(float, float, float) { return Vector(); } // object specific surface normal algorithm
};

}

#endif
