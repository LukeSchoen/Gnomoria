#include "Renderer.h"
#include "WorldDraw.h"
#include "WorldAccess.h"
#include "WorldOcclusion.h"
#include "Tile.h"



WorldDraw *WorldDraw::GetInstance()
{
  static WorldDraw *instance;
  if (!instance) instance = new WorldDraw();
  return instance;
}

RenderObject WorldDraw::BuildRegionMesh(Vec2i pos, Vec2i size, int layer)
{
  RenderObject region(0);
  region.ReAllocate(size.x * size.y * 5*2);
  region.AssignTexture("Assets\\Textures\\Texture.bmp");
  WorldAccess &world = *WorldAccess::GetInstance();

  for (int y = 0; y < size.y; y++)
  {
    for (int x = 0; x < size.x; x++)
    {
      Vec3i blockPos = WorldOcclusion_Solve(Vec2i(x, y) + pos, layer);

      uint8_t blockID = world.GetBlock(blockPos).floorType;

      switch (blockID)
      {
      case 1: blockID = 1; break;
      case 2: blockID = 4; break;
      case 3: blockID = 2; break;
      case 4: blockID = 0; break;
      case 8: blockID = 6; break;
      case 9: blockID = 6; break;
      case 12: blockID = 5; break;
      default: blockID = 7; break;
      }

      //Floor
      if (blockID > 0)
      {
        Tile_AddTile(region, blockPos, Vec3(1.0, 1.0, 1.0), 16 + blockID, Vec2i(0, 0));
      }

    }
  }
  return region;
}



