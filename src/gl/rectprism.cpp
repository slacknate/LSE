#include <new>
#include <cmath>
#include "gl/rectprism.h"
using namespace LSE;

/*
Initialize our prism. Store size attributes
and allocate all necessary memory.
*/
GLRectPrism::GLRectPrism(float x, float y, float z, float w, float h, float d) : GLPrimitive(x, y, z) {
    
    width = w;
    height = h;
    depth = d;
    
    MemAllocate(this->RECTP_VERT_COUNT, this->RECTP_ELEM_COUNT);
}

/*
Predefined rectangular prism vertices.
*/
void GLRectPrism::CalcVertices() {
    
    // front face
    
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
    
    // right face
    
    // v4
    vertices[12] = width/2.0f;
    vertices[13] = -height/2.0f;
    vertices[14] = -depth/2.0f;
    
    // v5
    vertices[15] = width/2.0f;
    vertices[16] = -height/2.0f;
    vertices[17] = depth/2.0f;
    
    // v6
    vertices[18] = width/2.0f;
    vertices[19] = height/2.0f;
    vertices[20] = depth/2.0f;
    
    // v7
    vertices[21] = width/2.0f;
    vertices[22] = height/2.0f;
    vertices[23] = -depth/2.0f;
    
    // top face
    
    // v8
    vertices[24] = -width/2.0f;
    vertices[25] = height/2.0f;
    vertices[26] = -depth/2.0f;
    
    // v9
    vertices[27] = width/2.0f;
    vertices[28] = height/2.0f;
    vertices[29] = -depth/2.0f;
    
    // v10
    vertices[30] = width/2.0f;
    vertices[31] = height/2.0f;
    vertices[32] = depth/2.0f;
    
    // v11
    vertices[33] = -width/2.0f;
    vertices[34] = height/2.0f;
    vertices[35] = depth/2.0f;
    
    // left face
    
    // v12
    vertices[36] = -width/2.0f;
    vertices[37] = -height/2.0f;
    vertices[38] = depth/2.0f;
    
    // v13
    vertices[39] = -width/2.0f;
    vertices[40] = -height/2.0f;
    vertices[41] = -depth/2.0f;
    
    // v14
    vertices[42] = -width/2.0f;
    vertices[43] = height/2.0f;
    vertices[44] = -depth/2.0f;
    
    // v15
    vertices[45] = -width/2.0f;
    vertices[46] = height/2.0f;
    vertices[47] = depth/2.0f;
    
    // bottom face
    
    // v16
    vertices[48] = -width/2.0f;
    vertices[49] = -height/2.0f;
    vertices[50] = depth/2.0f;
    
    // v17
    vertices[51] = width/2.0f;
    vertices[52] = -height/2.0f;
    vertices[53] = depth/2.0f;
    
    // v18
    vertices[54] = width/2.0f;
    vertices[55] = -height/2.0f;
    vertices[56] = -depth/2.0f;
    
    // v19
    vertices[57] = -width/2.0f;
    vertices[58] = -height/2.0f;
    vertices[59] = -depth/2.0f;
    
    // back face
    
    // v20
    vertices[60] = width/2.0f;
    vertices[61] = -height/2.0f;
    vertices[62] = depth/2.0f;
    
    // v21
    vertices[63] = -width/2.0f;
    vertices[64] = -height/2.0f;
    vertices[65] = depth/2.0f;
    
    // v22
    vertices[66] = -width/2.0f;
    vertices[67] = height/2.0f;
    vertices[68] = depth/2.0f;
    
    // v23
    vertices[69] = width/2.0f;
    vertices[70] = height/2.0f;
    vertices[71] = depth/2.0f;
}

/*
Tell OpenGL which vertices to use,
and where.
*/
void GLRectPrism::CalcIndices() {
    
    // front
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
    
    // right
    indices[6] = 4;
    indices[7] = 5;
    indices[8] = 6;
    indices[9] = 4;
    indices[10] = 6;
    indices[11] = 7;
    
    // top
    indices[12] = 8;
    indices[13] = 9;
    indices[14] = 10;
    indices[15] = 8;
    indices[16] = 10;
    indices[17] = 11;
    
    // left
    indices[18] = 12;
    indices[19] = 13;
    indices[20] = 14;
    indices[21] = 12;
    indices[22] = 14;
    indices[23] = 15;
    
    // bottom
    indices[24] = 16;
    indices[25] = 17;
    indices[26] = 18;
    indices[27] = 16;
    indices[28] = 18;
    indices[29] = 19;
    
    // back
    indices[30] = 20;
    indices[31] = 21;
    indices[32] = 22;
    indices[33] = 20;
    indices[34] = 22;
    indices[35] = 23;
}
