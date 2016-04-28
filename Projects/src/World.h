#ifndef World_h__
#define World_h__

#include "Math/Vector.h"
#include <stdio.h>
#include <stdint.h>

#include <glm.hpp>

void World_LoadWorld();
void World_BuildMesh();

uint8_t *World_LoadFromSchematic(char *MapPath, int &width, int &height, int &depth);

void World_Update();

//Helper
bool World_IsBlockExposed(uint8_t *world, int w, int h, int l, int x, int y, int z);
uint32_t World_SafeGetBlock(uint8_t *world, int w, int h, int l, int x, int y, int z);

glm::vec3 World_Solve(uint8_t *world, int w, int h, int l, int x, int z); //Occlusion Solving

glm::ivec3 World_ScreenToWorld(glm::vec2 ScreenPos);

#endif // World_h__
