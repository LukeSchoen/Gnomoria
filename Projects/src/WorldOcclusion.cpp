#include "WorldOcclusion.h"
#include "camera.h"
#include <cstdint>
#include "WorldAccess.h"

Vec3i WorldOcclusion_Solve(Vec2i startPos, int startLayer)
{
  Vec3i pos = Vec3i(startPos.x + startLayer, startLayer, startPos.y + startLayer);
  static Vec3i step(-1, -1, -1);
  while (true)
  {
    if (pos.y < 0) return Vec3i(-1, -1, -1);
    Block block = WorldAccess::GetInstance()->GetBlock(pos);
    if (block.floorType > 0) return pos;
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