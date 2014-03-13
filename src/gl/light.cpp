#include "gl/light.h"

/*
Initialize the paramaters. Set all
values to zero.
*/
LSE_GLLight::LSE_GLLight() {
    
    for(int i = 0; i < 24; ++i)
        parameters[i] = 0.0f;
}

/*
fix me -> need implementation
*/
void LSE_GLLight::Render() {
    
    
}

/*

*/
void LSE_GLLight::SetPosition(float x, float y, float z, float w) {
    
    parameters[0] = x;
    parameters[1] = y;
    parameters[2] = z;
    parameters[3] = w;
}

/*

*/
void LSE_GLLight::SetAmbient(float x, float y, float z, float w) {
    
    parameters[4] = x;
    parameters[5] = y;
    parameters[6] = z;
    parameters[7] = w;
}

/*

*/
void LSE_GLLight::SetDiffuse(float x, float y, float z, float w) {
    
    parameters[8] = x;
    parameters[9] = y;
    parameters[10] = z;
    parameters[11] = w;
}

/*

*/
void LSE_GLLight::SetSpecular(float x, float y, float z, float w) {
    
    parameters[12] = x;
    parameters[13] = y;
    parameters[14] = z;
    parameters[15] = w;
}

/*

*/
void LSE_GLLight::SetSpotDirection(float x, float y, float z) {
    
    parameters[16] = x;
    parameters[17] = y;
    parameters[18] = z;
}

/*

*/
void LSE_GLLight::SetSpotExponent(float x) {
    
    parameters[19] = x;
}

/*

*/
void LSE_GLLight::SetSpotCutoff(float x) {
    
    parameters[20] = x;
}

/*

*/
void LSE_GLLight::SetConstAtten(float x) {
    
    parameters[21] = x;
}

/*

*/
void LSE_GLLight::SetLinearAtten(float x) {
    
    parameters[22] = x;
}

/*

*/
void LSE_GLLight::SetQuadAtten(float x) {
    
    parameters[23] = x;
}
