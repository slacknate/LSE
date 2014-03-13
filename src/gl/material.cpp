#include "gl/material.h"

/*
Initialize the paramaters. Set all
values to zero.
*/
LSE_GLMaterial::LSE_GLMaterial() {
    
    for(int i = 0; i < 24; ++i)
        parameters[i] = 0.0f;
}

/*

*/
void LSE_GLMaterial::Bind() {
    
    
}

/*

*/
void LSE_GLMaterial::Unbind() {
    
    
}

/*

*/
void LSE_GLMaterial::SetAmbient(float x, float y, float z, float w) {
    
    parameters[0] = x;
    parameters[1] = y;
    parameters[2] = z;
    parameters[3] = w;
}

/*

*/
void LSE_GLMaterial::SetDiffuse(float x, float y, float z, float w) {
    
    parameters[4] = x;
    parameters[5] = y;
    parameters[6] = z;
    parameters[7] = w;
}

/*

*/
void LSE_GLMaterial::SetSpecular(float x, float y, float z, float w) {
    
    parameters[8] = x;
    parameters[9] = y;
    parameters[10] = z;
    parameters[11] = w;
}

/*

*/
void LSE_GLMaterial::SetEmission(float x, float y, float z, float w) {
    
    parameters[12] = x;
    parameters[13] = y;
    parameters[14] = z;
    parameters[15] = w;
}

/*

*/
void LSE_GLMaterial::SetAmbAndDiff(float x, float y, float z, float w) {
    
    parameters[16] = x;
    parameters[17] = y;
    parameters[18] = z;
    parameters[19] = w;
}

/*

*/
void LSE_GLMaterial::SetColorIndices(float x, float y, float z) {
    
    parameters[20] = x;
    parameters[21] = y;
    parameters[22] = z;
}

/*

*/
void LSE_GLMaterial::SetShininess(float x) {
    
    parameters[23] = x;
}
