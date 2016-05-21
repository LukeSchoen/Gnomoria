#ifndef Transforms_h__
#define Transforms_h__

#include "Math/Vector.h"

//Space Transforms
Vec2 Transform_ScreenToDevice(Vec2i ScreenPos);

Vec2 Transform_DeviceToIso(Vec2 mousePos);

Vec3 Transform_OrthoToIso(Vec3 Pos);

Vec2 Transform_IsoToOrtho(Vec2 IsoPos);

Vec3i Transform_ScreenToWorld(Vec2i ScreenPos);

Vec3i Transform_BlockToChunk(Vec3i value);

#endif // Transforms_h__