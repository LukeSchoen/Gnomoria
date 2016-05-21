#include "Tile.h"
#include "Renderer.h"
#include "Transforms.h"

void Tile_AddTile(RenderObject &renderer, Vec3i pos, Vec3 col, int TexID, Vec2i pixelOffset)
{
  TexID--;
  Vec3 iso = Transform_OrthoToIso((Vec3)pos);
  iso.y = 0;

  int AtlasTileWidth = 16;
  float iATW = 1.0f / AtlasTileWidth;
  int tx = TexID % AtlasTileWidth;
  int ty = TexID / AtlasTileWidth;
  float u = tx * iATW;
  float v = ty * iATW;

  float x = pixelOffset.x / 16.0f;
  float y = pixelOffset.y / 16.0f;

  renderer.AddQuad(
    Vert(
      Vec3(iso.x + x, iso.y, iso.z / 2.0f + y),
      Vec3(col.r, col.g, col.b),
      Vec2(u, v)),
    Vert(
      Vec3(iso.x + 2 + x, iso.y, iso.z / 2.0f + y),
      Vec3(col.r, col.g, col.b),
      Vec2(u + iATW, v)),
    Vert(
      Vec3(iso.x + 2 + x, iso.y, iso.z / 2.0f + 2.0f + y),
      Vec3(col.r, col.g, col.b),
      Vec2(u + iATW, v + iATW)),
    Vert(
      Vec3(iso.x + x, iso.y, iso.z / 2.0f + 2.0f + y),
      Vec3(col.r, col.g, col.b),
      Vec2(u, v + iATW))
    );
}
