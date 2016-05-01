#ifndef debug_h__
#define debug_h__

#include "Math/Vector.h"

struct RenderObject;

void Debug_Draw();

void Debug_Clear();

void Debug_AddFloorLine(Vec3i pos, Vec3 col);
void Debug_AddFloorFill(Vec3i pos, Vec3 col);

void Debug_AddWallLine(Vec3i pos, Vec3 col);
void Debug_AddWallFill(Vec3i pos, Vec3 col);

#endif //debug