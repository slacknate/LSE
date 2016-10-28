#ifndef LSE_GL_OBJ_H
#define LSE_GL_OBJ_H

#include "phy/object.h"
#include "gl/program.h"
#include "gl/material.h"
#include "util/math/matrix.h"
#include "util/math/quaternion.h"

namespace LSE {

/*
Base class for all objects which are drawable
on an OpenGL canvas.
*/
class GLObject : public PHObject {
    
    protected:
        
        GLProgram program; // shader program
        Quaternion rotation; // object orientation
        Matrix translation; // object translation

    public:
        
        GLObject(float x, float y, float z);
        
        GLProgram* GetProgram();
        
        void translate(Vector& v);
        void rotate(Quaternion& q);
        
        void Render();

        /*
         * Method to create all OpenGL relevant data
         * in memory prior to being drawn.
         */
        virtual void create()=0;

        /*
         * FIXME: should these be pure virtual?
         */
        virtual void Draw() {} // object specific render method
        virtual void RenderNormals() {} // object specific normal render method
        virtual bool Hit(float, float, float) { return false; } // collision detection method
        virtual Vector GetNormalAt(float, float, float) { return Vector(); } // object specific surface normal algorithm
};

}

#endif
