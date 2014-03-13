// transformation matrices
uniform mat4 MODEL_MAT;
uniform mat4 PROJ_MAT;

// vertex attributes
in vec3 VERT_POSITION;
in vec3 VERT_NORMAL;
in vec4 VERT_COLOR;
in vec2 VERT_TEX_COORD;

// output vertex data
out VertexData {
    vec3 position;    
    vec3 normal;
    vec4 color;
    vec2 texCoord;
} VertexOut;

// shader program
void main(void) {
    
    VertexOut.position = VERT_POSITION;
    VertexOut.normal = VERT_NORMAL;
    VertexOut.color = VERT_COLOR;
    VertexOut.texCoord = VERT_TEX_COORD;
    
    gl_Position = MODEL_MAT * PROJ_MAT * vec4(VERT_POSITION, 1.0);
}
