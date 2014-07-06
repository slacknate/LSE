#ifndef LSE_TERRAIN_2D_H
#define LSE_TERRAIN_2D_H

typedef float **Terrain2D;

Terrain2D GenTerrain2D(int seed, float startX, float startZ, int width, int depth, float low, float high);
void Free2D(Terrain2D *points, int width, int sampleRate);

#endif
