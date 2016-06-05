#include "WorldPaths.h"
#include <stdio.h>

static char TempPath[256];

char* WorldMainPath(char* worldPath)
{
  sprintf(TempPath, "Assets\\Worlds\\%s\\", worldPath);
  return TempPath;
}

char* WorldChunksPath(char* worldPath)
{
  sprintf(TempPath, "Assets\\Worlds\\%s\\chunks\\", worldPath);
  return TempPath;
}

char* WorldSizePath(char* worldPath)
{
  sprintf(TempPath, "Assets\\Worlds\\%s\\dimensions", worldPath);
  return TempPath;
}

char* WorldChunkName(Vec3i chunkPos, char* prefix)
{
  static char chunkName[256];
  sprintf(chunkName, "%s%d.%d.chunk", prefix, chunkPos.x, chunkPos.z);
  return chunkName;
}
