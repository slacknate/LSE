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
        Quaternion quat; // object orientation
        
        virtual void CalcNormals() {} // calculate normal vectors to all surfaces
        
    public:
        
        GLObject(double x, double y, double z);
        
        GLProgram* GetProgram();
        
        void Move(double dX, double dY, double dZ);
        void Transform(Quaternion& q);
        
        void Render();
        
        virtual void Draw() {} // object specific render method
        virtual void RenderNormals() {} // object specific normal render method
        virtual bool Hit(double, double, double) { return false; } // collision detection method
        virtual Vector GetNormalAt(double, double, double) { return Vector(); } // object specific surface normal algorithm
};

}

#endif
