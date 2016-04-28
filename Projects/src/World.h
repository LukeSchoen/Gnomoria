#ifndef World_h__
#define World_h__

#include <stdio.h>
#include <stdint.h>

#include "Math/Vector.h"

void World_LoadWorld();
void World_BuildMesh();

uint8_t *World_LoadFromSchematic(char *MapPath, int &width, int &height, int &depth);

//Helper
bool World_IsBlockExposed(uint8_t *world, int w, int h, int l, int x, int y, int z);

uint32_t World_GetBlock(Vec3i position);

void World_SetBlock(Vec3i position, uint32_t blockID);

Vec3i World_Solve(int x, int z); //Occlusion Solving

#endif // World_h__
