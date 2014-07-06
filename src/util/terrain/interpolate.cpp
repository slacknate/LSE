#include <cstdlib>
#include "util/terrain/interpolate.h"

float CubicInterpolate(float *interp, float x) {

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

float BicubicInterpolate(float *interp, float x, float y) {
    
    if(interp != NULL) {
        
        float columns[4];
    
        columns[0] = CubicInterpolate(&interp[0], y);
        columns[1] = CubicInterpolate(&interp[4], y);
        columns[2] = CubicInterpolate(&interp[8], y);
        columns[3] = CubicInterpolate(&interp[12], y);
        
        return CubicInterpolate(columns, x);
    }
    
    return 0.0;
}

float TricubicInterpolate(float *interp, float x, float y, float z) {
    
    if(interp != NULL) {

        float columns[4];
    
        columns[0] = BicubicInterpolate(&interp[0], x, y);
        columns[1] = BicubicInterpolate(&interp[16], x, y);
        columns[2] = BicubicInterpolate(&interp[32], x, y);
        columns[3] = BicubicInterpolate(&interp[48], x, y);
    
        return CubicInterpolate(columns, z);
    }
    
    return 0.0;
}
