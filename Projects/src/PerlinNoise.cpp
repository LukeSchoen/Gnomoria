#include "PerlinNoise.h"
#include <math.h>
#include <assert.h>

uint16_t PerlinNoiseGenerator::Seed()
{
  return _seed;
}

void PerlinNoiseGenerator::SetSeed(uint16_t seed)
{
  _seed = seed;
}

uint8_t PerlinNoiseGenerator::RandomByte(int x)
{
  x = (x << 13) ^ x;
  return (uint8_t)(1.0 + (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0) / 2.0 * 255);
}

double PerlinNoiseGenerator::Noise(double x, double y, int layer)
{
  x = (_seed * 985) + (layer * 654321) + x / (1 << layer);
  y = (layer * 984653) + y / (1 << layer);

  double tx = x - (int)x;
  double ty = y - (int)y;

  double top, bot;

  int p1 = RandomByte((int)x + (int)y * 123456) > 128;
  int p2 = RandomByte((int)x + 1 + (int)y * 123456) > 128;
  int p3 = RandomByte((int)x + ((int)y + 1) * 123456) > 128;
  int p4 = RandomByte((int)x + 1 + ((int)y + 1) * 123456) > 128;

  top = p1 * (1.0 - tx) + p2 * tx;
  bot = p3 * (1.0 - tx) + p4 * tx;

  double res = (bot * ty + top * (1.0 - ty));
  return res;
}

NoiseMap PerlinNoiseGenerator::GeneratePerlinNoise(int width, int height, int Layers)
{
  NoiseMap map(Vec2i(width, height));
  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      double Value = 0;
      for (int Layer = 0; Layer < Layers; Layer++)
      {
        Value += (Noise(x, y, Layer + 1)) * (1 << Layer);
      }
      Value /= ((1 << (Layers)) - 1);
      map.SetValue(Vec2i(x, y), Value);
    }
  }
  return map;
}

float NoiseMap::GetValue(Vec2i pos) const
{
  if (!(pos.x >= 0) && (pos.x < size.x) && (pos.y >= 0) && (pos.y < size.y))
    assert(false);
  return data[pos.x + pos.y * size.x];
}

void NoiseMap::SetValue(Vec2i pos, float value)
{
  if (!(pos.x >= 0) && (pos.x < size.x) && (pos.y >= 0) && (pos.y < size.y))
    assert(false);
  data[pos.x + pos.y * size.x] = value;
}
