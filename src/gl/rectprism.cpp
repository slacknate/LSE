#include <new>
#include <cmath>
#include "gl/rectprism.h"
using namespace LSE;

/*
 * Initialize our prism.
 */
GLRectPrism::GLRectPrism(float x, float y, float z, float w, float h, float d) :
        GLPrimitive(RECTP_VERT_COUNT, RECTP_NORM_COUNT, RECTP_ELEM_COUNT, x, y, z) {
    
    width = w;
    height = h;
    depth = d;
}

/*
 * Predefined rectangular prism vertices.
 * FIXME: comments don't actually match vertex positions...
 */
void GLRectPrism::calc_vertices() {
    
    /* v0 - back bottom right */
    vertices[0] = -width/2.0f;
    vertices[1] = -height/2.0f;
    vertices[2] = -depth/2.0f;

    /* v1 - back bottom right */
    vertices[3] = width/2.0f;
    vertices[4] = -height/2.0f;
    vertices[5] = -depth/2.0f;

    /* v2 - back top left */
    vertices[6] = width/2.0f;
    vertices[7] = height/2.0f;
    vertices[8] = -depth/2.0f;

    /* v3 - back top left */
    vertices[9] = -width/2.0f;
    vertices[10] = height/2.0f;
    vertices[11] = -depth/2.0f;

    /* v4 - front bottom right */
    vertices[12] = width/2.0f;
    vertices[13] = -height/2.0f;
    vertices[14] = depth/2.0f;

    /* v5 - front top right */
    vertices[15] = -width/2.0f;
    vertices[16] = -height/2.0f;
    vertices[17] = depth/2.0f;

    /* v6 - front top left */
    vertices[18] = -width/2.0f;
    vertices[19] = height/2.0f;
    vertices[20] = depth/2.0f;

    /* v7 - front bottom left */
    vertices[21] = width/2.0f;
    vertices[22] = height/2.0f;
    vertices[23] = depth/2.0f;

    /* front - v0, v1, v2, v3 */
    vert_indices[0] = 0;
    vert_indices[1] = 1;
    vert_indices[2] = 2;
    vert_indices[3] = 0;
    vert_indices[4] = 2;
    vert_indices[5] = 3;

    /* right - v2, v3, v4, v5 */
    vert_indices[6] = 1;
    vert_indices[7] = 4;
    vert_indices[8] = 7;
    vert_indices[9] = 1;
    vert_indices[10] = 7;
    vert_indices[11] = 2;

    /* top - v2, v3, v5, v6 */
    vert_indices[12] = 6;
    vert_indices[13] = 3;
    vert_indices[14] = 2;
    vert_indices[15] = 7;
    vert_indices[16] = 6;
    vert_indices[17] = 2;

    /* left - v0, v1, v6, v7 */
    vert_indices[18] = 0;
    vert_indices[19] = 5;
    vert_indices[20] = 6;
    vert_indices[21] = 0;
    vert_indices[22] = 3;
    vert_indices[23] = 6;

    /* bottom - v0, v3, v4, v7 */
    vert_indices[24] = 0;
    vert_indices[25] = 1;
    vert_indices[26] = 4;
    vert_indices[27] = 0;
    vert_indices[28] = 4;
    vert_indices[29] = 5;

    /* back - v4, v5, v6, v7 */
    vert_indices[30] = 4;
    vert_indices[31] = 5;
    vert_indices[32] = 6;
    vert_indices[33] = 4;
    vert_indices[34] = 6;
    vert_indices[35] = 7;
}

#include <cstdio>
/*
Calculate the normal to every surface
of this primitive.
fix me -> this is causing some serious errors....
*/
void GLRectPrism::calc_normals(){

    /* Front face */

    // create two vectors using the vertex coordinates
    Vector vec1(vertices[3] - vertices[0], vertices[4] - vertices[1], vertices[5] - vertices[2]);
    Vector vec2(vertices[3] - vertices[6], vertices[4] - vertices[7], vertices[5] - vertices[8]);

    // calculate the cross product, and normalize it
    Vector front_norm = vec1 % vec2;
    front_norm.normalize();

    // n0-v0
    normals[0] = vertices[0];
    normals[1] = vertices[1];
    normals[2] = vertices[2];

    // n0-v1
    normals[3] = vertices[0] + front_norm.i();
    normals[4] = vertices[1] + front_norm.j();
    normals[5] = vertices[2] + front_norm.k();

    // n0-i
    norm_indices[0] = 0;
    norm_indices[1] = 1;

    // n1-v0
    normals[6] = vertices[3];
    normals[7] = vertices[4];
    normals[8] = vertices[5];

    // n1-v1
    normals[9] = vertices[3] + front_norm.i();
    normals[10] = vertices[4] + front_norm.j();
    normals[11] = vertices[5] + front_norm.k();

    // n1-i
    norm_indices[2] = 2;
    norm_indices[3] = 3;

    // n2-v0
    normals[12] = vertices[6];
    normals[13] = vertices[7];
    normals[14] = vertices[8];

    // n2-v1
    normals[15] = vertices[6] + front_norm.i();
    normals[16] = vertices[7] + front_norm.j();
    normals[17] = vertices[8] + front_norm.k();

    // n2-i
    norm_indices[4] = 4;
    norm_indices[5] = 5;

    // n3-v0
    normals[18] = vertices[9];
    normals[19] = vertices[10];
    normals[20] = vertices[11];

    // n3-v1
    normals[21] = vertices[9] + front_norm.i();
    normals[22] = vertices[10] + front_norm.j();
    normals[23] = vertices[11] + front_norm.k();

    // n3-i
    norm_indices[6] = 6;
    norm_indices[7] = 7;
}
