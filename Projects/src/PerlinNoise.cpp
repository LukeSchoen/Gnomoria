#include "PerlinNoise.h"


PerlinNoiseGenerator::PerlinNoiseGenerator(uint16_t seed)
{
  _seed = seed;
}

uint16_t PerlinNoiseGenerator::Seed()
{
  return _seed;
}

uint8_t PerlinNoiseGenerator::RandomByte(int x)
{
  x = (x << 13) ^ x;
  return (uint8_t)(1.0 + (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0) / 2.0 * 255);
}

uint8_t PerlinNoiseGenerator::noise(double x, double y, int layer)
{
  x = (_seed * 985) + (layer * 654321) + x / (1 << layer);
  y = (layer * 984653) + y / (1 << layer);

  double tx = x - (int)x;
  double ty = y - (int)y;

  double top, bot;

  int p1 = RandomByte((int)x + (int)y * 123456);
  int p2 = RandomByte((int)x + 1 + (int)y * 123456);
  int p3 = RandomByte((int)x + ((int)y + 1) * 123456);
  int p4 = RandomByte((int)x + 1 + ((int)y + 1) * 123456);

  top = p1 * (1.0 - tx) + p2 * tx;
  bot = p3 * (1.0 - tx) + p4 * tx;

  uint8_t res = (uint8_t)(bot * ty + top * (1.0 - ty));
  return res;
}

uint8_t* PerlinNoiseGenerator::GeneratePerlinNoise(int width, int height, int Layers)
{
  uint8_t* buffer = new uint8_t[width*height];
  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      double Value = 0;
      for (int Layer = 0; Layer < Layers; Layer++)
      {
        Value += (noise(x, y, Layer + 1) / 255.0) * (1 << Layer);
      }
      Value /= ((1 << (Layers)) - 1);
      Value *= 255;
      buffer[x + y*width] = (uint8_t)Value;
    }
  }
  return buffer;
}
