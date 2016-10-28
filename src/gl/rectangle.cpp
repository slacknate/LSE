#include "gl/rectangle.h"
using namespace LSE;

/*
Initialize our quad. Store size attributes
and allocate all necessary memory.
*/
GLRectangle::GLRectangle(float x, float y, float z, float w, float h) :
        GLPrimitive(QUAD_VERT_COUNT, QUAD_ELEM_COUNT, x, y, z) {
    
    width = w;
    height = h;
}

/*
Predefined quad vertices.
*/
void GLRectangle::calc_vertices(){
    
    // v0
    vertices[0] = -width/2.0;
    vertices[1] = -height/2.0;
    vertices[2] = this->pos.z;
    
    // v1
    vertices[3] = width/2.0;
    vertices[4] = -height/2.0;
    vertices[5] = this->pos.z;
    
    // v2
    vertices[6] = width/2.0;
    vertices[7] = height/2.0;
    vertices[8] = this->pos.z;
    
    // v3
    vertices[9] = -width/2.0;
    vertices[10] = height/2.0;
    vertices[11] = this->pos.z;
}

/*
Tell OpenGL which vertices to use,
and where.
*/
void GLRectangle::calc_indices() {
    
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
}

/*

*/
void GLRectangle::calc_tex_coords(){
    
    // v0
    tex_coords[0] = 0;
    tex_coords[1] = 0;
    
    // v1
    tex_coords[2] = 1;
    tex_coords[3] = 0;
    
    // v2
    tex_coords[4] = 1;
    tex_coords[5] = 1;
    
    // v3
    tex_coords[6] = 0;
    tex_coords[7] = 1;
}
