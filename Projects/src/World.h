#ifndef World_h__
#define World_h__

#include <stdio.h>
#include <stdint.h>

#include "Math/Vector.h"

void World_LoadWorld();
void World_BuildMesh();
void World_Draw();

void World_AddTile(int posx, int posy, int posz, Vec3 col, int tex, int xpixoffset = 0, int ypixoffset = 0);

uint8_t *World_LoadFromSchematic(char *MapPath, int &width, int &height, int &depth);

Vec3i World_Solve(int x, int z); //occlusion solve

bool World_IsBlockExposed(uint8_t *world, int w, int h, int l, int x, int y, int z); //occlusion check

uint32_t World_GetBlock(Vec3i position);

void World_SetBlock(Vec3i position, uint32_t blockID);

#endif // World_h__
