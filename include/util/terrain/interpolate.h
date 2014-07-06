#ifndef LSE_INTERPOLATE_H
#define LSE_INTERPOLATE_H

float CubicInterpolate(float *interp, float x);
float BicubicInterpolate(float *interp, float x, float y);
float TricubicInterpolate(float *interp, float x, float y, float z);

#endif
