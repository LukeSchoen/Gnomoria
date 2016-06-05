#ifndef ChunkCache_h__
#define ChunkCache_h__

#include "Chunk.h"
#include "Math/Vector.h"

struct ChunkCache
{
public:
  Chunk &GetChunk(Vec3i blockPos);
  void SetChunk(Vec3i blockPos);
  void SetFolder(char* directory);
  void SaveChunks();
private:
  char* chunkPath = nullptr;
};

#endif ChunkCache_h__