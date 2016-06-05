#ifndef WorldDraw_h__
#define WorldDraw_h__

#include "Math/Vector.h"


struct RenderObject;

struct WorldDraw
{
  static WorldDraw *GetInstance();

  RenderObject BuildRegionMesh(Vec2i pos, Vec2i size, int layer);

};


#endif // WorldDraw_h__
