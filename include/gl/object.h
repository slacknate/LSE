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
        GLProgram norm_program; // shader program
        Quaternion rotation; // object orientation
        Matrix translation; // object translation

        virtual void draw()=0; // object specific render method
        virtual void draw_normals()=0; // object specific normal render method

    public:
        
        GLObject(float x, float y, float z);
        
        GLProgram* GetProgram();
        
        void translate(Vector& v);
        void rotate(Quaternion& q);
        
        void render(bool show_normals=false);

        /*
         * Method to create all OpenGL relevant data
         * in memory prior to being drawn.
         */
        virtual void create()=0;

        virtual bool Hit(float, float, float)=0; // object specific collision detection
        virtual Vector GetNormalAt(float, float, float)=0; // object specific surface normal algorithm
};

}

#endif
