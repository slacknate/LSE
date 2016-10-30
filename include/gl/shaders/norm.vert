// transformation matrices
uniform mat4 VIEW_MAT;
uniform mat4 PROJ_MAT;
uniform mat4 TRANS_MAT;
uniform mat4 ROT_MAT;

// vertex attributes
in vec3 VERT_POSITION;

// shader program
void main(void) {
    
    gl_Position = PROJ_MAT * VIEW_MAT * TRANS_MAT * ROT_MAT * vec4(VERT_POSITION, 1.0);
}
