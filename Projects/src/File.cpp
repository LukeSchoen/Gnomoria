#include "File.h"
#include <stdio.h>
#include <assert.h>


void WriteFile(char* filePath, void* fileData, int fileSize)
{
  FILE* file = fopen(filePath, "wb");
  if (file)
  {
    fwrite(fileData, fileSize, 1, file);
    fclose(file);
  }
  else assert(false); // file cannot be opened or created!
}

void ReadFile(char* filePath, void* fileData, int fileSize)
{
  FILE* file = fopen(filePath, "rb");
  if (file)
  {
    fread(fileData, fileSize, 1, file);
    fclose(file);
  }
  else assert(false); // file cannot be opened or read!
}
