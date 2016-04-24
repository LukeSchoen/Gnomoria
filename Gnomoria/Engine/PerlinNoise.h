#include<cstdint>

struct PerlinNoiseGenerator
{
private:
  uint16_t _seed;
public:
  PerlinNoiseGenerator(uint16_t seed = 0);
  static uint8_t RandomByte(int x);
  uint8_t noise(double x, double y, int layer);
  uint8_t* GeneratePerlinNoise(int width, int height, int Layers);
  uint16_t Seed();
};