#include "ChunkCache.h"
#include "Transforms.h"
#include "ChronoCache.h"
#include <assert.h>
#include <stdio.h>
#include "GString.h"

const int CacheSize = 512;
ChronoCache chunkCache(CacheSize);
Chunk chunkData[CacheSize];
bool chunkChanged[CacheSize] = { false };
Vec3i chunkLocation[CacheSize];

int64_t hashVec3i(Vec3i value)
{
  return value.x + (int64_t(value.y) << 20) + (int64_t(value.z) << 40);
}

char* BlockPosToChunkName(Vec3i BlockPosition, char* prefix = nullptr)
{
  static char chunkName[256];
  Vec3i chunkPos = Transform_BlockToChunk(BlockPosition);
  sprintf(chunkName, "%s%d.%d.chunk", prefix, chunkPos.x, chunkPos.z);
  return chunkName;
}

void ChunkCache::SetFolder(char* directory)
{
  delete[] chunkPath;
  chunkPath = strcpy(directory);
}

void ChunkCache::SaveChunks()
{
  for (int chunkID = 0; chunkID < CacheSize; chunkID++)
    if (chunkChanged[chunkID])
    {
      Chunk_Save(BlockPosToChunkName(chunkLocation[chunkID], chunkPath), &chunkData[chunkID]);
      chunkChanged[chunkID] = false;
    }
}

Chunk &ChunkCache::GetChunk(Vec3i blockPos)
{
  int64_t hash = hashVec3i(Transform_BlockToChunk(blockPos));
  bool Loaded;
  int cacheLoc = chunkCache.GetDataAddress(hash, Loaded);
  if (!Loaded)
  {
    if (chunkChanged[cacheLoc]) // Save the previously loaded chunk if it has been changed
      Chunk_Save(BlockPosToChunkName(chunkLocation[cacheLoc], chunkPath), &chunkData[cacheLoc]);
    Chunk_Load(BlockPosToChunkName(blockPos, chunkPath), &chunkData[cacheLoc]);
    chunkChanged[cacheLoc] = false;
    chunkLocation[cacheLoc] = blockPos;
  }
  return chunkData[cacheLoc];
}

void ChunkCache::SetChunk(Vec3i blockPos)
{
  int64_t hash = hashVec3i(Transform_BlockToChunk(blockPos));
  bool Loaded;
  int cacheLoc = chunkCache.GetDataAddress(hash, Loaded);
  if (!Loaded) assert(false); //Attempt to tag an unloaded chunk as being modified!
  chunkChanged[cacheLoc] = true;
}

