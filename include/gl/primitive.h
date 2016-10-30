#ifndef LSE_GL_PRIM_H
#define LSE_GL_PRIM_H

#include "util/math/vector.h"
#include "gl/object.h"
#include "gl/program.h"

/*
TODO:
    add texture
*/

namespace LSE {

/*
Base class for OpenGL 2D and 3D primitives.
*/
class GLPrimitive : public GLObject {
    
    protected:        
        
        int num_vertices; // number of vertices that make up this primitive
        int num_normals; // number of normal vectors that make up this primitive
        int num_elements; // number of elements that make up this primitive

        float *vertices;
        int *vert_indices;

        float *normals;
        int *norm_indices;

        float *colors;
        int *tex_coords;

        void draw();
        void draw_normals();

        bool SameSide(Vertex &vertA, Vertex &vertB, Vertex &vertC, Vertex &vertD);
        bool InTriangle(Vertex &vertA, Vertex &vertB, Vertex &vertC, Vertex &ref, float x, float y, float z);

        virtual void calc_normals()=0; // calculate normal vectors to all surfaces
        virtual void calc_colors()=0; // primitive specific color initialization method
        virtual void calc_vertices()=0; // primitive specific vertex creation method
        virtual void calc_tex_coords()=0; // primitive specific texture coordinate creation method

    public:

        GLPrimitive(unsigned int nv, unsigned int nn, unsigned int ne, float x, float y, float z);
        ~GLPrimitive();

        void create();

        bool Hit(float x, float y, float z);
        Vector GetNormalAt(float x, float y, float z);
};

}

#endif
