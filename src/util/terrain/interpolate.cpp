#include <cstdlib>
#include "util/terrain/interpolate.h"

float LSE_CubicInterpolate(float *interp, float x) {

    if(interp != NULL) {

        float x3 = x*x*x;
        float x2 = x*x;
	
        float P = (interp[3] - interp[2]) - (interp[0] - interp[1]);
    	float Q = (interp[0] - interp[1]) - P;
        float R = interp[2] - interp[0];
    	float S = interp[1];
    
	   return (P * x3) + (Q * x2) + (R * x) + S;
    }
    
    return 0.0;
}

float LSE_BicubicInterpolate(float *interp, float x, float y) {
    
    if(interp != NULL) {
        
        float columns[4];
    
        columns[0] = LSE_CubicInterpolate(&interp[0], y);
        columns[1] = LSE_CubicInterpolate(&interp[4], y);
        columns[2] = LSE_CubicInterpolate(&interp[8], y);
        columns[3] = LSE_CubicInterpolate(&interp[12], y);
        
        return LSE_CubicInterpolate(columns, x);
    }
    
    return 0.0;
}

float LSE_TricubicInterpolate(float *interp, float x, float y, float z) {
    
    if(interp != NULL) {

        float columns[4];
    
        columns[0] = LSE_BicubicInterpolate(&interp[0], x, y);
        columns[1] = LSE_BicubicInterpolate(&interp[16], x, y);
        columns[2] = LSE_BicubicInterpolate(&interp[32], x, y);
        columns[3] = LSE_BicubicInterpolate(&interp[48], x, y);
    
        return LSE_CubicInterpolate(columns, z);
    }
    
    return 0.0;
}
