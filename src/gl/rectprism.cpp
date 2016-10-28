#include <new>
#include <cmath>
#include "gl/rectprism.h"
using namespace LSE;

/*
Initialize our prism. Store size attributes
and allocate all necessary memory.
*/
GLRectPrism::GLRectPrism(float x, float y, float z, float w, float h, float d) :
        GLPrimitive(RECTP_VERT_COUNT, RECTP_ELEM_COUNT, x, y, z) {
    
    width = w;
    height = h;
    depth = d;
}

/*
Predefined rectangular prism vertices.
*/
void GLRectPrism::calc_vertices(){
    
    // v0
    vertices[0] = -width/2.0f;
    vertices[1] = -height/2.0f;
    vertices[2] = -depth/2.0f;
    
    // v1
    vertices[3] = width/2.0f;
    vertices[4] = -height/2.0f;
    vertices[5] = -depth/2.0f;
    
    // v2
    vertices[6] = width/2.0f;
    vertices[7] = height/2.0f;
    vertices[8] = -depth/2.0f;
    
    // v3
    vertices[9] = -width/2.0f;
    vertices[10] = height/2.0f;
    vertices[11] = -depth/2.0f;

    // v4
    vertices[12] = width/2.0f;
    vertices[13] = -height/2.0f;
    vertices[14] = depth/2.0f;

    // v5
    vertices[15] = -width/2.0f;
    vertices[16] = -height/2.0f;
    vertices[17] = depth/2.0f;

    // v6
    vertices[18] = -width/2.0f;
    vertices[19] = height/2.0f;
    vertices[20] = depth/2.0f;

    // v7
    vertices[21] = width/2.0f;
    vertices[22] = height/2.0f;
    vertices[23] = depth/2.0f;
}

/*
Calculate the normal to every surface
of this primitive.
fix me -> this is causing some serious errors....
*/
void GLRectPrism::calc_normals(){

    // loop through each strip
    for(int i = 0; i < numElements; ++i) {

        // calculate vertex array indices
        int vert_one = indices[(3*i)];
        int vert_two = indices[(3*i)+1];
        int vert_three = indices[(3*i)+2];

        // get each vertex for this triangle
        Vertex vert1(vertices[(3*vert_one)], vertices[(3*vert_one)+1], vertices[(3*vert_one)+2]);
        Vertex vert2(vertices[(3*vert_two)], vertices[(3*vert_two)+1], vertices[(3*vert_two)+2]);
        Vertex vert3(vertices[(3*vert_three)], vertices[(3*vert_three)+1], vertices[(3*vert_three)+2]);

        // create two vectors using the vertex coordinates
        Vector vec1(vert2.x - vert1.x, vert2.y - vert1.y, vert2.z - vert1.z);
        Vector vec2(vert2.x - vert3.x, vert2.y - vert3.y, vert2.z - vert3.z);

        // calculate the cross product, and normalize it
        Vector normal = vec1 % vec2;
        normal.normalize();

        // store our result in the normal array (note: need a normal per vertex)
        normals[(3*vert_one)] = normal.i();
        normals[(3*vert_one)+1] = normal.j();
        normals[(3*vert_one)+2] = normal.k();

        normals[(3*vert_two)+3] = normal.i();
        normals[(3*vert_two)+4] = normal.j();
        normals[(3*vert_two)+5] = normal.k();

        normals[(3*vert_three)+6] = normal.i();
        normals[(3*vert_three)+7] = normal.j();
        normals[(3*vert_three)+8] = normal.k();
    }
}

/*
Tell OpenGL which vertices to use,
and where.
*/
void GLRectPrism::calc_indices() {
    
    // front
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
    
    // right
    indices[6] = 1;
    indices[7] = 4;
    indices[8] = 7;
    indices[9] = 1;
    indices[10] = 7;
    indices[11] = 2;
    
    // top
    indices[12] = 6;
    indices[13] = 3;
    indices[14] = 2;
    indices[15] = 7;
    indices[16] = 6;
    indices[17] = 2;
    
    // left
    indices[18] = 0;
    indices[19] = 5;
    indices[20] = 6;
    indices[21] = 0;
    indices[22] = 3;
    indices[23] = 6;
    
    // bottom
    indices[24] = 0;
    indices[25] = 1;
    indices[26] = 4;
    indices[27] = 0;
    indices[28] = 4;
    indices[29] = 5;
    
    // back
    indices[30] = 4;
    indices[31] = 5;
    indices[32] = 6;
    indices[33] = 4;
    indices[34] = 6;
    indices[35] = 7;
}
