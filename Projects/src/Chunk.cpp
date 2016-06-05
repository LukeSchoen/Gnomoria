#include "Chunk.h"
#include <stdio.h>
#include <assert.h>

void Chunk_Load(char* chunkPath, void* memoryLocation)
{
  FILE* file = fopen(chunkPath, "rb");
  if (file)
  {
    fread(memoryLocation, Chunk::dataSize, 1, file);
    fclose(file);
  }
  else assert(false); //Chunk file was not found
}

void Chunk_Save(char* chunkPath, void* memoryLocation)
{
  FILE* file = fopen(chunkPath, "wb");
  if (file)
  {
    fwrite(memoryLocation, Chunk::dataSize, 1, file);
    fclose(file);
  }
  else assert(false); // Chunk file cannot be opened or created!
}