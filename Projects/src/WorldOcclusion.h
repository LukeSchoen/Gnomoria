#ifndef WorldOcclusion_h__
#define worldOcclusion_h__
#include "Math/Vector.h"

bool WorldOcclusion_Visable(Vec3i pos);

Vec3i WorldOcclusion_Solve(Vec2i pos, int startLayer);

#endif // worldOcclusion_h__
