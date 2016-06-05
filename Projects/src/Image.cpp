#include "Image.h"
#include "sdl.h"


Image::Image(int width, int height)
{
  surface = SDL_CreateRGBSurface(0, width, height, 24, 0, 0, 0, 0);
}

void Image::SetPixel(int x, int y, uint32_t col)
{
  uint8_t *c = (uint8_t*)&col;
  uint8_t r = c[0];
  uint8_t g = c[1];
  uint8_t b = c[2];
  ((uint8_t*)surface->pixels)[x * 3 + y * surface->pitch + 0] = r;
  ((uint8_t*)surface->pixels)[x * 3 + y * surface->pitch + 1] = g;
  ((uint8_t*)surface->pixels)[x * 3 + y * surface->pitch + 2] = b;
}

uint32_t Image::GetPixel(int x, int y)
{
  uint32_t col;
  uint8_t *c = (uint8_t*)&col;
  uint8_t r = c[0];
  uint8_t g = c[1];
  uint8_t b = c[2];
  r = ((uint8_t*)surface->pixels)[x * 3 + y * surface->pitch + 0];
  g = ((uint8_t*)surface->pixels)[x * 3 + y * surface->pitch + 1];
  b = ((uint8_t*)surface->pixels)[x * 3 + y * surface->pitch + 2];
  return col;
}

void Image::Save(char* filePath)
{
  SDL_SaveBMP(surface, filePath);
}

void Image::Load(char* filePath)
{
  surface = SDL_LoadBMP(filePath);
}
