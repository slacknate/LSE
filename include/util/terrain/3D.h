#ifndef LSE_TERRAIN_3D_H
#define LSE_TERRAIN_3D_H

typedef float ***LSE_Terrain3D;

LSE_Terrain3D LSE_GenTerrain3D(int seed, float startX, float startY, float startZ, int width, int height, int depth, float low, float high);
void LSE_Free3D(LSE_Terrain3D *points, int width, int height, int sampleRate);

#endif
