#include "gl/light.h"
using namespace LSE;

/*
Initialize the paramaters. Set all
values to zero.
*/
GLLight::GLLight() {
    
    for(int i = 0; i < 24; ++i)
        parameters[i] = 0.0f;
}

/*
fix me -> need implementation
*/
void GLLight::Render() {
    
    
}

/*

*/
void GLLight::SetPosition(float x, float y, float z, float w) {
    
    parameters[0] = x;
    parameters[1] = y;
    parameters[2] = z;
    parameters[3] = w;
}

/*

*/
void GLLight::SetAmbient(float x, float y, float z, float w) {
    
    parameters[4] = x;
    parameters[5] = y;
    parameters[6] = z;
    parameters[7] = w;
}

/*

*/
void GLLight::SetDiffuse(float x, float y, float z, float w) {
    
    parameters[8] = x;
    parameters[9] = y;
    parameters[10] = z;
    parameters[11] = w;
}

/*

*/
void GLLight::SetSpecular(float x, float y, float z, float w) {
    
    parameters[12] = x;
    parameters[13] = y;
    parameters[14] = z;
    parameters[15] = w;
}

/*

*/
void GLLight::SetSpotDirection(float x, float y, float z) {
    
    parameters[16] = x;
    parameters[17] = y;
    parameters[18] = z;
}

/*

*/
void GLLight::SetSpotExponent(float x) {
    
    parameters[19] = x;
}

/*

*/
void GLLight::SetSpotCutoff(float x) {
    
    parameters[20] = x;
}

/*

*/
void GLLight::SetConstAtten(float x) {
    
    parameters[21] = x;
}

/*

*/
void GLLight::SetLinearAtten(float x) {
    
    parameters[22] = x;
}

/*

*/
void GLLight::SetQuadAtten(float x) {
    
    parameters[23] = x;
}
