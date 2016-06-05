#ifndef Chunk_h__
#define Chunk_h__
#include "Block.h"

struct Chunk
{
  static const int width = 16;
  static const int height = 256;
  static const int length = 16;
  static const int dataSize = (width * height * length) * sizeof(Block);
  Block Data[width * height * length];
};


void Chunk_Load(char* chunkPath, void* memoryLocation);

void Chunk_Save(char* chunkPath, void* memoryLocation);

#endif Chunk_h__