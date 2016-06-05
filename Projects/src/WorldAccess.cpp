#include "WorldAccess.h"
#include "Block.h"
#include "Chunk.h"
#include "Transforms.h"
#include "ChunkCache.h"
#include "Math\Vector.h"
#include "WorldPaths.h"
#include "File.h"
#include "GString.h"

ChunkCache Chunks;

WorldAccess *WorldAccess::GetInstance()
{
  static WorldAccess *instance;
  if (!instance) instance = new WorldAccess();
  return instance;
}


Vec3i WorldAccess::GetSize()
{
  return worldSize;
}


void WorldAccess::Save(char* folderPath)
{
  //Flush chunk modifications
  Chunks.SaveChunks();
  //Store Path to chunk files
  Loaded = true;
  delete[] worldFilePath;
  worldFilePath = strcpy(folderPath);
  Chunks.SetFolder(WorldChunksPath(folderPath));
  //TODO
  //here we should be moving the modified version of world over the original project path
  //for now we are just working directly in the original project path
}

void WorldAccess::Load(char* folderPath)
{
  //Store Path to chunk files
  Loaded = true;
  delete[] worldFilePath;
  worldFilePath = strcpy(folderPath);
  Chunks.SetFolder(WorldChunksPath(folderPath));
  ReadFile(WorldSizePath(folderPath), &worldSize, sizeof(worldSize));
}

Block WorldAccess::GetBlock(Vec3i BlockWorldPos)
{
  Chunk &chunk = Chunks.GetChunk(BlockWorldPos);
  Vec3i cpos = Transform_BlockToChunk(BlockWorldPos);
  int x = BlockWorldPos.x - cpos.x * Chunk::width;
  int y = BlockWorldPos.y - cpos.y * Chunk::height;
  int z = BlockWorldPos.z - cpos.z * Chunk::length;
  return chunk.Data[x + z * Chunk::width + y * Chunk::width * Chunk::length];
}

void WorldAccess::SetBlock(Vec3i BlockWorldPos, Block newBlock)
{
  Chunk &chunk = Chunks.GetChunk(BlockWorldPos);
  Vec3i cpos = Transform_BlockToChunk(BlockWorldPos);
  int x = BlockWorldPos.x - cpos.x * Chunk::width;
  int y = BlockWorldPos.y - cpos.y * Chunk::height;
  int z = BlockWorldPos.z - cpos.z * Chunk::length;
  chunk.Data[x + z * Chunk::width + y * Chunk::width * Chunk::length] = newBlock;
  Chunks.SetChunk(BlockWorldPos);
}
