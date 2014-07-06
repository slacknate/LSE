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
        
        int numVertices; // number of vertices that make up this primitive
        int numElements; // number of elements that make up this primitive
        double *vertices;
        double *normals;
        double *colors;
        int *texCoords;
        int *indices;
        bool initialized; // true when memory allocation has succeeded and all vertices and normals have been calculated
        
        bool SameSide(Vertex &vertA, Vertex &vertB, Vertex &vertC, Vertex &vertD);
        bool InTriangle(Vertex &vertA, Vertex &vertB, Vertex &vertC, Vertex &ref, double x, double y, double z);
        void CalcNormals();
        void MemAllocate(int nv, int ne);
        
        virtual void CalcColors(); // primitive specific color initialization method
        virtual void CalcVertices() {} // primitive specific vertex creation method
        virtual void CalcIndices() {} // primitive specific index creation method
        virtual void CalcTexCoords() {} // primitive specific texture coordinate creation method
        
    public:
        
        GLPrimitive(double x, double y, double z);
        ~GLPrimitive();
        
        //void Transform(Quaternion& q);
        void Draw();
        void RenderNormals();
        bool Hit(double x, double y, double z);
        Vector GetNormalAt(double x, double y, double z);
};

}

#endif
