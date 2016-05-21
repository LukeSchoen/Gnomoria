#include "ChunkCache.h"
#include <assert.h>
#include "Transforms.h"
#include "DenseHashMap.h"

struct Node
{
  int backPtr;
  int chunkID;
};

const int cacheSize = 512;

Chunk chunks[cacheSize];

int queFrontPtr = 0;
int queBackPtr = -1;
int queCount = 0;

Node priorityQue[cacheSize];



int64_t chunkHash[cacheSize];
bool chunkLoaded[cacheSize] = { false };
int chunkLastAccess[cacheSize];
DenseHashMap chunkLookup(cacheSize);


static char chunkName[256];

int64_t hashVec3i(Vec3i value)
{
  return value.x + (int64_t(value.y) << 20) + (int64_t(value.z) << 40);
}

char* BlockPosToChunkName(Vec3i BlockPosition, char* prefix = nullptr)
{
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

void SaveChunk(Vec3i blockPos)
{

}

void ChunkCache::SetFolder(char* directory)
{
  chunkPath = directory;
}


int findNextFreeChunk()
{
  for (int chunkID = 0; chunkID < cacheSize; chunkID++)
    if (chunkLoaded[chunkID] == false)
      return chunkID;
  return -1; // no more space!
}

void FreeOldestChunk()
{
  int OldestChunkID = -1;
  int OldestChunkAge = 0;
  for (int chunkID = 0; chunkID < cacheSize; chunkID++)
    if (chunkLoaded[chunkID])
      if (chunkLastAccess[chunkID] > OldestChunkAge)
      {
        OldestChunkID = chunkID;
        OldestChunkAge = chunkLastAccess[chunkID];
      }
  if (OldestChunkID >= 0)
  {//Drop chunk which has not been recently accessed
    chunkLoaded[OldestChunkID] = false;
    chunkLookup.Delete(chunkHash[OldestChunkID]);
  }
}

Chunk &ChunkCache::GetChunk(Vec3i blockPos)
{
  int64_t chunkID;
  int64_t hash = hashVec3i(Transform_BlockToChunk(blockPos));
  if(!chunkLookup.Obtain(hash, chunkID))
  {
    //int newChunkID;
    //if (queCount < cacheSize)
    //{
    //  Node &oldQueNode = priorityQue[queFrontPtr];
    //  oldQueNode.backPtr = queCount;
    //  queFrontPtr = queCount;
    //  Node &queNode = priorityQue[queCount];
    //  queNode.chunkID = queCount;
    //  newChunkID = queCount;
    //  queCount++;
    //}
    //else
    //{
    //  chunkLookup.Delete();
    //}

    int newChunkID = findNextFreeChunk();
    if (newChunkID == -1)
    {
      FreeOldestChunk();
      newChunkID = findNextFreeChunk();
    }

    chunkLoaded[newChunkID] = true;
    char* chunkName = BlockPosToChunkName(blockPos, chunkPath);
    LoadChunk(chunkName, &chunks[newChunkID]);
    int64_t hash = hashVec3i(Transform_BlockToChunk(blockPos));
    chunkLookup.Insert(hash, newChunkID);
    chunkHash[newChunkID] = hash;
    for (int chunkID = 0; chunkID < cacheSize; chunkID++)
      chunkLastAccess[chunkID]++; // Age all cached chunks

    chunkLastAccess[newChunkID] = 0;

    return chunks[newChunkID];
  }
  else
  {
    return chunks[chunkID];
  }
}

void ChunkCache::SetChunk(Vec3i blockPos, Chunk &NewChunk)
{

}

