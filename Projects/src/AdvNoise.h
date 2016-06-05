#ifndef AdvNoise_h__
#define AdvNoise_h__
#include "PerlinNoise.h"

struct AdvNoise
{
  static NoiseMap SampleWithTurbulance(NoiseMap source, int TurbulanceOctaves, int TurbulanceMagnitude);
};


#endif // AdvNoise_h__
