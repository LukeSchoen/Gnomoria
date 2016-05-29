#include "Transforms.h"
#include "camera.h"
#include "renderer.h"
#include "world.h"
#include "chunk.h"
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

Vec3 Transform_OrthoToIso(Vec3 Pos)
{
  float isoX = Pos.x - Pos.z;
  float isoY = Pos.y;
  float isoZ = Pos.x + Pos.z - Pos.y * 2;
  return Vec3(isoX, isoY, isoZ);
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

Vec3i Transform_BlockToChunk(Vec3i value)
{
  static int offset = 10000;
  static Vec3i coffset(offset * Chunk::width, 0, offset * Chunk::length);
  //Truncation is not the same as floor for negatives so we use an offset to keep things always positive
  value += coffset;
  return Vec3i(value.x / Chunk::width - offset, value.y / Chunk::height, value.z / Chunk::length - offset);
}
