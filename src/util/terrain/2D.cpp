#include <new>
#include <cstdlib>
#include <anl/anl.h>
#include "util/terrain/2D.h"
#include "util/terrain/interpolate.h"


/*
TODO:
    why do some sample rates cause segfaults?
*/
Terrain2D InterpNoise2D(float startX, float startZ, int width, int depth, int sampleRate, float low, float high, anl::CImplicitFractal& fractal) {
    
    Terrain2D points = NULL; // terrain data
    
    if(sampleRate > 1) {
        
        /*
        We need to create a memory space larger than the desired dimensions
        in order to be able to interpolate at the edges of our terrain.
        */
        int modWidth = width + (2 * sampleRate);
        int modDepth = depth + (2 * sampleRate);
        
        points = new (std::nothrow) float *[modWidth];
        bool widthSucceed = (points != NULL);
        
        if(widthSucceed) {
            
            bool depthSucceed = true;
            for(int w = 0; w < modWidth; ++w) {
                
                points[w] = new (std::nothrow) float [modDepth];
                depthSucceed &= (points[w] != NULL);
            }
            
            if(depthSucceed) {
                
                for(int w = 0; w < modWidth; w += sampleRate) {
                    
                    for(int d = 0; d < modDepth; d += sampleRate) {
                        
                        points[w][d] = fractal.get(startX + float(w), startZ + float(d));
                        
                        if(d == 0)
                            --d;
                    }
                    
                    if(w == 0)
                        --w;
                }
                    
                float interpPoints[16];
                    
                for(int w = sampleRate; w < sampleRate + width; ++w) {
                    
                    for(int d = sampleRate; d < sampleRate + depth; ++d) {
                            
                        int p1X = w - (w % sampleRate) - 1;
                        int p0X = p1X - sampleRate + 1;
                        int p2X = p1X + sampleRate;
                        int p3X = p1X + (2 * sampleRate);
                            
                        int p1Y = d - (d % sampleRate) - 1;
                        int p0Y = p1Y - sampleRate + 1;
                        int p2Y = p1Y + sampleRate;
                        int p3Y = p1Y + (2 * sampleRate);
                                    
                        interpPoints[0] = points[p0X][p0Y];
                        interpPoints[1] = points[p0X][p1Y];
                        interpPoints[2] = points[p0X][p2Y];
                        interpPoints[3] = points[p0X][p3Y];
                        interpPoints[4] = points[p1X][p0Y];
                        interpPoints[5] = points[p1X][p1Y];
                        interpPoints[6] = points[p1X][p2Y];
                        interpPoints[7] = points[p1X][p3Y];
                        interpPoints[8] = points[p2X][p0Y];
                        interpPoints[9] = points[p2X][p1Y];
                        interpPoints[10] = points[p2X][p2Y];
                        interpPoints[11] = points[p2X][p3Y];
                        interpPoints[12] = points[p3X][p0Y];
                        interpPoints[13] = points[p3X][p1Y];
                        interpPoints[14] = points[p3X][p2Y];
                        interpPoints[15] = points[p3X][p3Y];
                                    
                        float x = float(w - p1X)/float(sampleRate);
                        float y = float(d - p1Y)/float(sampleRate);
                        points[w][d] = BicubicInterpolate(interpPoints, x, y);
                    }
                }
            }
        }
    }
                
    return points;
}

Terrain2D GenTerrain2D(int seed, float startX, float startZ, int width, int depth, float low, float high) {
    
    int sampleRates[4];
    sampleRates[0] = 8;
    sampleRates[1] = 16;
    sampleRates[2] = 32;
    sampleRates[3] = 128;
    
    anl::CImplicitFractal f0(anl::FBM, anl::SIMPLEX, anl::CUBIC);
    f0.setSeed(seed);
    f0.setNumOctaves(3);
	f0.setFrequency(0.157);
	f0.setGain(10.362);
	f0.setLacunarity(float(sampleRates[0]));
	
	anl::CImplicitFractal f1(anl::FBM, anl::SIMPLEX, anl::CUBIC);
    f1.setSeed(seed);
    f1.setNumOctaves(3);
	f1.setFrequency(0.872);
	f1.setGain(2479.789);
	f1.setLacunarity(float(sampleRates[1]));
	
	anl::CImplicitFractal f2(anl::FBM, anl::SIMPLEX, anl::CUBIC);
    f2.setSeed(seed);
    f2.setNumOctaves(3);
	f2.setFrequency(12.444);
	f2.setGain(37.556);
	f2.setLacunarity(float(sampleRates[2]));
	
	anl::CImplicitFractal f3(anl::FBM, anl::SIMPLEX, anl::CUBIC);
    f3.setSeed(seed);
    f3.setNumOctaves(3);
	f3.setFrequency(17.533);
	f3.setGain(5357.891);
	f3.setLacunarity(float(sampleRates[3]));
    
    Terrain2D p0 = InterpNoise2D(startX, startZ, width, depth, sampleRates[0], low, high, f0);
    Terrain2D p1 = InterpNoise2D(startX, startZ, width, depth, sampleRates[1], low, high, f1);
    Terrain2D p2 = InterpNoise2D(startX, startZ, width, depth, sampleRates[2], low, high, f2);
    Terrain2D p3 = InterpNoise2D(startX, startZ, width, depth, sampleRates[3], low, high, f3);
    
    Terrain2D points = NULL;
    
    if(p0 && p1 && p2 && p3) {
    
        points = new (std::nothrow) float *[width];
        bool widthSucceed = (points != NULL);
        
        if(widthSucceed) {
            
            bool depthSucceed = true;
            for(int w = 0; w < width; ++w) {
                
                points[w] = new (std::nothrow) float [depth];
                depthSucceed &= (points[w] != NULL);
            }
            
            if(depthSucceed) {
                
                for(int w = 0; w < width; ++w) {
                    
                    for(int d = 0; d < depth; ++d)
                        points[w][d] = 0.0;
                }
            
                for(int w = 0; w < width; ++w) {
                    
                    for(int d = 0; d < depth; ++d)
                        points[w][d] = (p0[w+sampleRates[0]][d+sampleRates[0]] + p1[w+sampleRates[1]][d+sampleRates[1]] + p2[w+sampleRates[2]][d+sampleRates[2]] + p3[w+sampleRates[3]][d+sampleRates[3]])/4.0;
                }
            }
        }
    }
    
    Free2D(&p0, width, sampleRates[0]);
    Free2D(&p1, width, sampleRates[1]);
    Free2D(&p2, width, sampleRates[2]);
    Free2D(&p3, width, sampleRates[3]);
    
    return points;
}

void Free2D(Terrain2D *points, int width, int sampleRate) {
    
    if(points) {
        
        int modWidth = width + (2 * sampleRate);
    
        for(int w = 0; w < modWidth; ++w) {
                    
            delete[] (*points)[w];
            (*points)[w] = NULL;
        }
    
        delete[] (*points);
        *points = NULL;
    }
}
