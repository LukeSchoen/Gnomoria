#ifndef WorldPaths_h__
#define WorldPaths_h__

#include "Math\Vector.h"

char* WorldMainPath(char* worldPath);

char* WorldChunksPath(char* worldPath);

char* WorldSizePath(char* worldPath);

char* WorldChunkName(Vec3i chunkPos, char* prefix = nullptr);

#endif // WorldPaths_h__
