#ifndef LSE_TERRAIN_2D_H
#define LSE_TERRAIN_2D_H

typedef float **LSE_Terrain2D;

LSE_Terrain2D LSE_GenTerrain2D(int seed, float startX, float startZ, int width, int depth, float low, float high);
void LSE_Free2D(LSE_Terrain2D *points, int width, int sampleRate);

#endif
