#ifndef LSE_INTERPOLATE_H
#define LSE_INTERPOLATE_H

float LSE_CubicInterpolate(float *interp, float x);
float LSE_BicubicInterpolate(float *interp, float x, float y);
float LSE_TricubicInterpolate(float *interp, float x, float y, float z);

#endif
