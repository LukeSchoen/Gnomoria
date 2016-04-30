#ifndef Transform_h__
#define Transform_h__

#include "camera.h"
#include "renderer.h"
#include "world.h"
#include "Math/Vector.h"
#include <math.h>

//Space Transforms
Vec2 Transform_ScreenToDevice(Vec2i ScreenPos)
{
  return (Vec2(ScreenPos.x / (SCREEN_WIDTH + 0.0), ScreenPos.y / (SCREEN_HEIGHT + 0.0)));
}

Vec2 Transform_DeviceToIso(Vec2 mousePos)
{
  float x = mousePos.x * 2 - 1;
  float y = mousePos.y * 2 - 1;
  cam& camPos = *cam::GetInstance();
  x = camPos.x + x *camPos.y *(SCREEN_WIDTH + 0.0f) / SCREEN_HEIGHT;
  y = camPos.z + y *camPos.y;
  return Vec2(x, y * 2);
}

Vec2 Transform_IsoToOrtho(Vec2 IsoPos)
{
  Vec2 i = IsoPos - Vec2(1, 1);
  Vec2 OrthoPos((i.y + i.x) / 2.0f, (i.y + i.x) / 2.0f - i.x);
  return OrthoPos;
}

Vec3i Transform_ScreenToWorld(Vec2i ScreenPos)
{
  Vec2 DeviceSpace = Transform_ScreenToDevice(ScreenPos);
  Vec2 IsoSpace = Transform_DeviceToIso(DeviceSpace);
  Vec2 OrthoSpace = Transform_IsoToOrtho(IsoSpace);
  return World_Solve((int)round(OrthoSpace.x), (int)round(OrthoSpace.y));
}

#endif // Transform_h__