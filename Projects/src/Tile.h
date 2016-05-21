#ifndef Tile_h__
#define Tile_h__

#include "Math/Vector.h"

struct RenderObject;

void Tile_AddTile(RenderObject &renderer, Vec3i pos, Vec3 col, int TexID, Vec2i pixelOffset);

#endif // Tile_h__
