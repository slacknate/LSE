#include "gl/material.h"
using namespace LSE;

/*
Initialize the paramaters. Set all
values to zero.
*/
GLMaterial::GLMaterial() {
    
    for(int i = 0; i < 24; ++i)
        parameters[i] = 0.0f;
}

/*

*/
void GLMaterial::Bind() {
    
    
}

/*

*/
void GLMaterial::Unbind() {
    
    
}

/*

*/
void GLMaterial::SetAmbient(float x, float y, float z, float w) {
    
    parameters[0] = x;
    parameters[1] = y;
    parameters[2] = z;
    parameters[3] = w;
}

/*

*/
void GLMaterial::SetDiffuse(float x, float y, float z, float w) {
    
    parameters[4] = x;
    parameters[5] = y;
    parameters[6] = z;
    parameters[7] = w;
}

/*

*/
void GLMaterial::SetSpecular(float x, float y, float z, float w) {
    
    parameters[8] = x;
    parameters[9] = y;
    parameters[10] = z;
    parameters[11] = w;
}

/*

*/
void GLMaterial::SetEmission(float x, float y, float z, float w) {
    
    parameters[12] = x;
    parameters[13] = y;
    parameters[14] = z;
    parameters[15] = w;
}

/*

*/
void GLMaterial::SetAmbAndDiff(float x, float y, float z, float w) {
    
    parameters[16] = x;
    parameters[17] = y;
    parameters[18] = z;
    parameters[19] = w;
}

/*

*/
void GLMaterial::SetColorIndices(float x, float y, float z) {
    
    parameters[20] = x;
    parameters[21] = y;
    parameters[22] = z;
}

/*

*/
void GLMaterial::SetShininess(float x) {
    
    parameters[23] = x;
}
