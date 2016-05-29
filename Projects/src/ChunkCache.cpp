#include "ChunkCache.h"
#include <assert.h>
#include "Transforms.h"
#include "ChronoCache.h"

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

void LoadChunk(char* chunkPath, void* memoryLocation)
{
  FILE* f = fopen(chunkPath, "rb");
  if (f)
  {
    fread(memoryLocation, Chunk::discSize, 1, f);
    fclose(f);
  }
  else
  {
    assert(false); //Chunk file not found
  }
}

void SaveChunk(char* chunkPath, void* memoryLocation)
{
  FILE* f = fopen(chunkPath, "wb");
  if (f)
  {
    fwrite(memoryLocation, Chunk::discSize, 1, f);
    fclose(f);
  }
  else
  {
    assert(false); // Chunk file cannot be opened or created!
  }
}

void ChunkCache::SetFolder(char* directory)
{
  chunkPath = directory;
}

Chunk &ChunkCache::GetChunk(Vec3i blockPos)
{
  int64_t hash = hashVec3i(Transform_BlockToChunk(blockPos));
  bool Loaded;
  int cacheLoc = chunkCache.GetDataAddress(hash, Loaded);
  if (!Loaded)
  {
    if (chunkChanged[cacheLoc]) // Save the previously loaded chunk if it has been changed
      SaveChunk(BlockPosToChunkName(chunkLocation[cacheLoc], chunkPath), &chunkData[cacheLoc]);
    LoadChunk(BlockPosToChunkName(blockPos, chunkPath), &chunkData[cacheLoc]);
    chunkChanged[cacheLoc] = false;
    chunkLocation[cacheLoc] = blockPos;
  }
  return chunkData[cacheLoc];
}

void ChunkCache::SetChunk(Vec3i blockPos, Chunk &NewChunk)
{
  int64_t hash = hashVec3i(blockPos);
  bool Loaded;
  int cacheLoc = chunkCache.GetDataAddress(hash, Loaded);
  if (!Loaded)
  {
    assert(false); //Attempt to modify an unloaded chunk!
  }
  chunkChanged[cacheLoc] = true;
}

