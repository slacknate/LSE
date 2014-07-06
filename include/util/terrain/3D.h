#ifndef LSE_TERRAIN_3D_H
#define LSE_TERRAIN_3D_H

typedef float ***Terrain3D;

Terrain3D GenTerrain3D(int seed, float startX, float startY, float startZ, int width, int height, int depth, float low, float high);
void Free3D(Terrain3D *points, int width, int height, int sampleRate);

#endif
