#ifndef Image_h__
#define Image_h__

#include <cstdint>

struct SDL_Surface;

struct Image
{
  Image(int width, int height);

  void SetPixel(int x, int y, uint32_t col);

  uint32_t GetPixel(int x, int y);

  void Save(char* filePath);

  void Load(char* filePath);

private:
  SDL_Surface* surface;

};

#endif // Image_h__
