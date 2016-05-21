#include "WorldAccess.h"
#include "Math\Vector.h"
#include "Chunk.h"
#include "Transforms.h"
#include "ChunkCache.h"
#include "Block.h"

ChunkCache Chunks;

WorldAccess *WorldAccess::GetInstance()
{
  static WorldAccess *instance;
  if (!instance) instance = new WorldAccess();
  return instance;
}

void WorldAccess::Save(char* folderPath)
{

}

void WorldAccess::Load(char* folderPath)
{
  Loaded = true;
  filePath = folderPath;
  //Store Path to chunk files
  static char chunkDir[256];
  sprintf(chunkDir, "%s\\chunks\\", folderPath);
  Chunks.SetFolder(chunkDir);
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
  int x = BlockWorldPos.x % Chunk::width;
  int y = BlockWorldPos.y % Chunk::height;
  int z = BlockWorldPos.z % Chunk::length;
  chunk.Data[x + z * Chunk::width + y * Chunk::width * Chunk::length] = newBlock;
  Chunks.SetChunk(BlockWorldPos, chunk);
}
