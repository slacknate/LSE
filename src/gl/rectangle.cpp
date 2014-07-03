#include "gl/rectangle.h"
using namespace LSE;

/*
Initialize our quad. Store size attributes
and allocate all necessary memory.
*/
LSE_GLRectangle::LSE_GLRectangle(double x, double y, double z, double w, double h)  : LSE_GLPrimitive(x, y, z) {
    
    width = w;
    height = h;
    
    MemAllocate(this->QUAD_VERT_COUNT, this->QUAD_ELEM_COUNT);
}

/*
Predefined quad vertices.
*/
void LSE_GLRectangle::CalcVertices() {
    
    // v0
    vertices[0] = -width/2.0;
    vertices[1] = -height/2.0;
    vertices[2] = pZ;
    
    // v1
    vertices[3] = width/2.0;
    vertices[4] = -height/2.0;
    vertices[5] = pZ;
    
    // v2
    vertices[6] = width/2.0;
    vertices[7] = height/2.0;
    vertices[8] = pZ;
    
    // v3
    vertices[9] = -width/2.0;
    vertices[10] = height/2.0;
    vertices[11] = pZ;
}

/*
Tell OpenGL which vertices to use,
and where.
*/
void LSE_GLRectangle::CalcIndices() {
    
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
}

/*

*/
void LSE_GLRectangle::CalcTexCoords() {
    
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
