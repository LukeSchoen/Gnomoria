#include "AdvNoise.h"

NoiseMap AdvNoise::SampleWithTurbulance(NoiseMap source, int TurbulanceOctaves, int TurbulanceMagnitude)
{
  PerlinNoiseGenerator perlinGenerator;
  perlinGenerator.SetSeed(1);
  NoiseMap xmap = perlinGenerator.GeneratePerlinNoise(source.size.x, source.size.y, TurbulanceOctaves);
  perlinGenerator.SetSeed(2);
  NoiseMap zmap = perlinGenerator.GeneratePerlinNoise(source.size.x, source.size.y, TurbulanceOctaves);

  NoiseMap ret(source.size - TurbulanceMagnitude);

  for (int y = 0; y < ret.size.y; y++)
  {
    for (int x = 0; x < ret.size.x; x++)
    {
      int xpos = x + (xmap.GetValue(Vec2i(x, y)) * TurbulanceMagnitude);
      int ypos = y + (zmap.GetValue(Vec2i(x, y)) * TurbulanceMagnitude);

      if (xpos < 0) xpos = 0;
      if (ypos < 0) ypos = 0;

      if (xpos >= source.size.x) xpos = source.size.x - 1;
      if (ypos >= source.size.y) ypos = source.size.y - 1;

      ret.SetValue(Vec2i(x, y), source.GetValue(Vec2i(xpos, ypos)));
    }
  }
  return ret;
}