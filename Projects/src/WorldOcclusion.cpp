#include "WorldOcclusion.h"
#include "camera.h"
#include <cstdint>
#include "WorldAccess.h"

Vec3i WorldOcclusion_Solve(Vec2i startPos, int startLayer)
{
  WorldAccess &world = *WorldAccess::GetInstance();
  Vec3i worldSize = world.GetSize();

  Vec3i pos = Vec3i(startPos.x + startLayer, startLayer, startPos.y + startLayer);
  static Vec3i step(-1, -1, -1);
  while (true)
  {
    if (pos.y < 0) return Vec3i(-1, -1, -1);

    if ((pos.x >= 0) & (pos.x < worldSize.x) & (pos.y >= 0) & (pos.y < worldSize.y) & (pos.z >= 0) & (pos.z < worldSize.z))
    {
      Block block = world.GetBlock(pos);
      if (block.floorType > 0) return pos;
    }
    pos += step;
  }
}

bool WorldOcclusion_Visable(Vec3i pos)
{
  int scrollHeight = cam::GetInstance()->scrollLayer;
  static Vec3i step(1, 1, 1);
  while (true)
  {
    if (pos.y >= scrollHeight) return true;
    Block block = WorldAccess::GetInstance()->GetBlock(pos);
    if (block.floorType > 0) return false;
    pos += step;
  }
}