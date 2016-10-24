#include <new>
#include <cstdlib>
#include "util/terrain/3D.h"
#include "util/terrain/interpolate.h"
#include "anl/anl.h"

/*
TODO:
    why do some sample rates cause segfaults?
*/
Terrain3D InterpNoise3D(float startX, float startY, float startZ, int width, int height, int depth, int sampleRate, float low, float high, anl::CImplicitFractal& fractal) {
    
    Terrain3D points = NULL;
    
    if(sampleRate > 1) {
        
        int modWidth = width + (2 * sampleRate);
        int modHeight = height + (2 * sampleRate);
        int modDepth = depth + (2 * sampleRate);
        
        points = new (std::nothrow) float **[modWidth];
        bool widthSucceed = (points != NULL);
        
        if(widthSucceed) {
            
            bool heightSucceed = true;
            for(int w = 0; w < modWidth; ++w) {
                
                points[w] = new (std::nothrow) float *[modHeight];
                heightSucceed &= (points[w] != NULL);
            }
            
            if(heightSucceed) {
                
                bool depthSucceed = true;
                for(int w = 0; w < modWidth; ++w) {
                    
                    for(int h = 0; h < modHeight; ++h) {
                        
                        points[w][h] = new (std::nothrow) float [modDepth];
                        depthSucceed &= (points[w][h] != NULL);
                    }
                }
                
                if(depthSucceed) {
                    
                    for(int w = 0; w < modWidth; w += sampleRate) {
                    
                        for(int h = 0; h < modHeight; h += sampleRate) {
                            
                            for(int d = 0; d < modDepth; d += sampleRate) {
                                
                                points[w][h][d] = fractal.get(startX + float(w), startY + float(h), startZ + float(d));
                                
                                if(d == 0)
                                    --d;
                            }
                            
                            if(h == 0)
                                --h;
                        }
                        
                        if(w == 0)
                            --w;
                    }
                    
                    float bciInterpPoints[16];
                    
                    for(int d = sampleRate; d < sampleRate + depth; d += sampleRate) {
                    
                        for(int w = sampleRate; w < sampleRate + width; ++w) {
                    
                            for(int h = sampleRate; h < sampleRate + height; ++h) {
                            
                                int p1X = w - (w % sampleRate) - 1;
                                int p0X = p1X - sampleRate + 1;
                                int p2X = p1X + sampleRate;
                                int p3X = p1X + (2 * sampleRate);
                            
                                int p1Y = h - (h % sampleRate) - 1;
                                int p0Y = p1Y - sampleRate + 1;
                                int p2Y = p1Y + sampleRate;
                                int p3Y = p1Y + (2 * sampleRate);
                                    
                                bciInterpPoints[0] = points[p0X][p0Y][d];
                                bciInterpPoints[1] = points[p0X][p1Y][d];
                                bciInterpPoints[2] = points[p0X][p2Y][d];
                                bciInterpPoints[3] = points[p0X][p3Y][d];
                                bciInterpPoints[4] = points[p1X][p0Y][d];
                                bciInterpPoints[5] = points[p1X][p1Y][d];
                                bciInterpPoints[6] = points[p1X][p2Y][d];
                                bciInterpPoints[7] = points[p1X][p3Y][d];
                                bciInterpPoints[8] = points[p2X][p0Y][d];
                                bciInterpPoints[9] = points[p2X][p1Y][d];
                                bciInterpPoints[10] = points[p2X][p2Y][d];
                                bciInterpPoints[11] = points[p2X][p3Y][d];
                                bciInterpPoints[12] = points[p3X][p0Y][d];
                                bciInterpPoints[13] = points[p3X][p1Y][d];
                                bciInterpPoints[14] = points[p3X][p2Y][d];
                                bciInterpPoints[15] = points[p3X][p3Y][d];
                                    
                                float x = float(w - p1X)/float(sampleRate);
                                float y = float(h - p1Y)/float(sampleRate);
                                
                                points[w][h][d] = BicubicInterpolate(bciInterpPoints, x, y);
                            }
                        }
                        
                        if(d == 0)
                            --d;
                    }
                    
                    float interpPoints[64];
                    
                    for(int w = sampleRate; w < sampleRate + width; ++w) {
                    
                        for(int h = sampleRate; h < sampleRate + height; ++h) {
                            
                            for(int d = sampleRate; d < sampleRate + depth; ++d) {
                                
                                int p1X = w - (w % sampleRate) - 1;
                                int p0X = p1X - sampleRate + 1;
                                int p2X = p1X + sampleRate;
                                int p3X = p1X + (2 * sampleRate);
                            
                                int p1Y = h - (h % sampleRate) - 1;
                                int p0Y = p1Y - sampleRate + 1;
                                int p2Y = p1Y + sampleRate;
                                int p3Y = p1Y + (2 * sampleRate);
                                    
                                int p1Z = d - (d % sampleRate) - 1;
                                int p0Z = p1Z - sampleRate + 1;
                                int p2Z = p1Z + sampleRate;
                                int p3Z = p1Z + (2 * sampleRate);
                                
                                interpPoints[0] = points[p0X][p0Y][p0Z];
                                interpPoints[1] = points[p0X][p1Y][p0Z];
                                interpPoints[2] = points[p0X][p2Y][p0Z];
                                interpPoints[3] = points[p0X][p3Y][p0Z];
                                interpPoints[4] = points[p1X][p0Y][p0Z];
                                interpPoints[5] = points[p1X][p1Y][p0Z];
                                interpPoints[6] = points[p1X][p2Y][p0Z];
                                interpPoints[7] = points[p1X][p3Y][p0Z];
                                interpPoints[8] = points[p2X][p0Y][p0Z];
                                interpPoints[9] = points[p2X][p1Y][p0Z];
                                interpPoints[10] = points[p2X][p2Y][p0Z];
                                interpPoints[11] = points[p2X][p3Y][p0Z];
                                interpPoints[12] = points[p3X][p0Y][p0Z];
                                interpPoints[13] = points[p3X][p1Y][p0Z];
                                interpPoints[14] = points[p3X][p2Y][p0Z];
                                interpPoints[15] = points[p3X][p3Y][p0Z];
                        
                                interpPoints[16] = points[p0X][p0Y][p1Z];
                                interpPoints[17] = points[p0X][p1Y][p1Z];
                                interpPoints[18] = points[p0X][p2Y][p1Z];
                                interpPoints[19] = points[p0X][p3Y][p1Z];
                                interpPoints[20] = points[p1X][p0Y][p1Z];
                                interpPoints[21] = points[p1X][p1Y][p1Z];
                                interpPoints[22] = points[p1X][p2Y][p1Z];
                                interpPoints[23] = points[p1X][p3Y][p1Z];
                                interpPoints[24] = points[p2X][p0Y][p1Z];
                                interpPoints[25] = points[p2X][p1Y][p1Z];
                                interpPoints[26] = points[p2X][p2Y][p1Z];
                                interpPoints[27] = points[p2X][p3Y][p1Z];
                                interpPoints[28] = points[p3X][p0Y][p1Z];
                                interpPoints[29] = points[p3X][p1Y][p1Z];
                                interpPoints[30] = points[p3X][p2Y][p1Z];
                                interpPoints[31] = points[p3X][p3Y][p1Z];
                        
                                interpPoints[32] = points[p0X][p0Y][p2Z];
                                interpPoints[33] = points[p0X][p1Y][p2Z];
                                interpPoints[34] = points[p0X][p2Y][p2Z];
                                interpPoints[35] = points[p0X][p3Y][p2Z];
                                interpPoints[36] = points[p1X][p0Y][p2Z];
                                interpPoints[37] = points[p1X][p1Y][p2Z];
                                interpPoints[38] = points[p1X][p2Y][p2Z];
                                interpPoints[39] = points[p1X][p3Y][p2Z];
                                interpPoints[40] = points[p2X][p0Y][p2Z];
                                interpPoints[41] = points[p2X][p1Y][p2Z];
                                interpPoints[42] = points[p2X][p2Y][p2Z];
                                interpPoints[43] = points[p2X][p3Y][p2Z];
                                interpPoints[44] = points[p3X][p0Y][p2Z];
                                interpPoints[45] = points[p3X][p1Y][p2Z];
                                interpPoints[46] = points[p3X][p2Y][p2Z];
                                interpPoints[47] = points[p3X][p3Y][p2Z];
                        
                                interpPoints[48] = points[p0X][p0Y][p3Z];
                                interpPoints[49] = points[p0X][p1Y][p3Z];
                                interpPoints[50] = points[p0X][p2Y][p3Z];
                                interpPoints[51] = points[p0X][p3Y][p3Z];
                                interpPoints[52] = points[p1X][p0Y][p3Z];
                                interpPoints[53] = points[p1X][p1Y][p3Z];
                                interpPoints[54] = points[p1X][p2Y][p3Z];
                                interpPoints[55] = points[p1X][p3Y][p3Z];
                                interpPoints[56] = points[p2X][p0Y][p3Z];
                                interpPoints[57] = points[p2X][p1Y][p3Z];
                                interpPoints[58] = points[p2X][p2Y][p3Z];
                                interpPoints[59] = points[p2X][p3Y][p3Z];
                                interpPoints[60] = points[p3X][p0Y][p3Z];
                                interpPoints[61] = points[p3X][p1Y][p3Z];
                                interpPoints[62] = points[p3X][p2Y][p3Z];
                                interpPoints[63] = points[p3X][p3Y][p3Z];
                                    
                                float x = float(w - p1X)/float(sampleRate);
                                float y = float(h - p1Y)/float(sampleRate);
                                float z = float(d - p1Z)/float(sampleRate);
                                points[w][h][d] = TricubicInterpolate(interpPoints, x, y, z);
                            }
                        }
                    }
                }
            }
        }
    }
                
    return points;
}

Terrain3D GenTerrain3D(int seed, float startX, float startY, float startZ, int width, int height, int depth, float low, float high) {
    
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
    
    Terrain3D p0 = InterpNoise3D(startX, startY, startZ, width, height, depth, sampleRates[0], low, high, f0);
    Terrain3D p1 = InterpNoise3D(startX, startY, startZ, width, height, depth, sampleRates[1], low, high, f1);
    Terrain3D p2 = InterpNoise3D(startX, startY, startZ, width, height, depth, sampleRates[2], low, high, f2);
    Terrain3D p3 = InterpNoise3D(startX, startY, startZ, width, height, depth, sampleRates[3], low, high, f3);
    
    Terrain3D points = NULL;
    
    if(p0 && p1 && p2 && p3) {
        
        points = new (std::nothrow) float **[width];
        bool widthSucceed = (points != NULL);
        
        if(widthSucceed) {
            
            bool heightSucceed = true;
            for(int w = 0; w < width; ++w) {
                
                points[w] = new (std::nothrow) float *[height];
                heightSucceed &= (points[w] != NULL);
            }
            
            if(heightSucceed) {
                
                bool depthSucceed = true;
                for(int w = 0; w < width; ++w) {
                    
                    for(int h = 0; h < height; ++h) {
                        
                        points[w][h] = new (std::nothrow) float [depth];
                        depthSucceed &= (points[w][h] != NULL);
                    }
                }
                
                if(depthSucceed) {
                
                    for(int w = 0; w < width; ++w) {
                    
                        for(int h = 0; h < height; ++h) {
                        
                            for(int d = 0; d < depth; ++d)
                                points[w][h][d] = 0.0;
                        }
                    }
                        
                    for(int w = 0; w < width; ++w) {
                        
                        for(int h = 0; h < height; ++h) {
                        
                            for(int d = 0; d < depth; ++d)
                                points[w][h][d] = (p0[w+sampleRates[0]][h+sampleRates[0]][d+sampleRates[0]] + p1[w+sampleRates[1]][h+sampleRates[1]][d+sampleRates[1]] + p2[w+sampleRates[2]][h+sampleRates[2]][d+sampleRates[2]] + p3[w+sampleRates[3]][h+sampleRates[3]][d+sampleRates[3]])/4.0;
                        }
                    }
                }
            }
        }
    }
    
    Free3D(&p0, width, height, sampleRates[0]);
    Free3D(&p1, width, height, sampleRates[1]);
    Free3D(&p2, width, height, sampleRates[2]);
    Free3D(&p3, width, height, sampleRates[3]);
    
    return points;
}

void Free3D(Terrain3D *points, int width, int height, int sampleRate) {
    
    if(points) {
    
        int modWidth = width + (2 * sampleRate);
        int modHeight = height + (2 * sampleRate);
    
        for(int w = 0; w < modWidth; ++w) {
                    
            for(int h = 0; h < modHeight; ++h) {
                                            
                delete[] (*points)[w][h];
                (*points)[w][h] = NULL;
            }
        
            delete[] (*points)[w];
            (*points)[w] = NULL;
        }
    
        delete[] (*points);
        *points = NULL;
    }
}
