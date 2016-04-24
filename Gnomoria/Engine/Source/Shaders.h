#include <stdio.h>

char* LoadShader(char* shaderpath)
{
  FILE * file;
  fopen_s(&file, shaderpath, "rb");
  if (!file)
  {
    printf("Shader could not be opened\n");
    return nullptr;
  }
  fseek(file, 0, SEEK_END);
  int shadersize = ftell(file);
  char* data = new char[shadersize + 1];
  data[shadersize] = NULL;
  fseek(file, 0, SEEK_SET);
  fread(data, 1, shadersize, file);
  fclose(file);
  return data;
}