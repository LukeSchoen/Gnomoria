#ifndef PerlinNoise_h__
#define PerlinNoise_h__

#include <cstdint>
#include "math/GMMath.h"
#include <string>

struct NoiseMap
{
  Vec2i size;
  float *data = nullptr;

  NoiseMap(Vec2i Size)
  {
    size = Size;
    data = new float[size.x * size.y];
  }

  NoiseMap(NoiseMap const& val)
  {
    *this = val;
  }

  NoiseMap(NoiseMap &&val)
  {
    *this = std::forward<NoiseMap>(val);
  }

  ~NoiseMap()
  {
    delete[] data;
  }

  float GetValue(Vec2i pos) const;

  void SetValue(Vec2i pos, float value);

  static NoiseMap FromIntersection(NoiseMap const &A, NoiseMap const &B)
  {
    Vec2i newSize(min(A.size.x, B.size.x), min(A.size.y, B.size.y));
    return NoiseMap(newSize);
  }

  NoiseMap& operator=(NoiseMap const &rhs)
  {
    size = rhs.size;
    delete[] data;
    data = new float[size.x * size.y];
    memcpy(data, rhs.data, sizeof(float) * size.x * size.y);
    return *this;
  }

  NoiseMap& operator=(NoiseMap &&rhs)
  {
    size = rhs.size;
    delete[] data;
    data = rhs.data;
    rhs.data = nullptr;
    return *this;
  }

  friend NoiseMap operator*(NoiseMap const &lhs, NoiseMap const &rhs)
  {
    NoiseMap ret = FromIntersection(lhs, rhs);
    for (int y = 0; y < ret.size.y; y++)
      for (int x = 0; x < ret.size.x; x++)
      {
        Vec2i pos(x, y);
        ret.SetValue(pos, lhs.GetValue(pos) * rhs.GetValue(pos));
      }
    return ret;
  }

  friend NoiseMap operator*(NoiseMap const &lhs, float rhs)
  {
    NoiseMap ret(lhs.size);
    for (int y = 0; y < ret.size.y; y++)
      for (int x = 0; x < ret.size.x; x++)
      {
        Vec2i pos(x, y);
        ret.SetValue(pos, lhs.GetValue(pos) * rhs);
      }
    return ret;
  }

  friend NoiseMap operator/(NoiseMap const &lhs, NoiseMap const &rhs)
  {
    NoiseMap ret = FromIntersection(lhs, rhs);
    for (int y = 0; y < ret.size.y; y++)
      for (int x = 0; x < ret.size.x; x++)
      {
        Vec2i pos(x, y);
        ret.SetValue(pos, lhs.GetValue(pos) / rhs.GetValue(pos));
      }
    return ret;
  }

  friend NoiseMap operator/(NoiseMap const &lhs, float rhs)
  {
    NoiseMap ret(lhs.size);
    for (int y = 0; y < ret.size.y; y++)
      for (int x = 0; x < ret.size.x; x++)
      {
        Vec2i pos(x, y);
        ret.SetValue(pos, lhs.GetValue(pos) / rhs);
      }
    return ret;
  }

  friend NoiseMap operator+(NoiseMap const &lhs, NoiseMap const &rhs)
  {
    NoiseMap ret = FromIntersection(lhs, rhs);
    for (int y = 0; y < ret.size.y; y++)
      for (int x = 0; x < ret.size.x; x++)
      {
        Vec2i pos(x, y);
        ret.SetValue(pos, lhs.GetValue(pos) + rhs.GetValue(pos));
      }
    return ret;
  }

  friend NoiseMap operator+(NoiseMap const &lhs, float rhs)
  {
    NoiseMap ret(lhs.size);
    for (int y = 0; y < ret.size.y; y++)
      for (int x = 0; x < ret.size.x; x++)
      {
        Vec2i pos(x, y);
        ret.SetValue(pos, lhs.GetValue(pos) + rhs);
      }
    return ret;
  }

  friend NoiseMap operator-(NoiseMap const &lhs, NoiseMap const &rhs)
  {
    NoiseMap ret = FromIntersection(lhs, rhs);
    for (int y = 0; y < ret.size.y; y++)
      for (int x = 0; x < ret.size.x; x++)
      {
        Vec2i pos(x, y);
        ret.SetValue(pos, lhs.GetValue(pos) - rhs.GetValue(pos));
      }
    return ret;
  }

  friend NoiseMap operator-(NoiseMap const &lhs, float rhs)
  {
    NoiseMap ret(lhs.size);
    for (int y = 0; y < ret.size.y; y++)
      for (int x = 0; x < ret.size.x; x++)
      {
        Vec2i pos(x, y);
        ret.SetValue(pos, lhs.GetValue(pos) - rhs);
      }
    return ret;
  }

  friend NoiseMap operator-(float lhs, NoiseMap const &rhs)
  {
    NoiseMap ret(rhs.size);
    for (int y = 0; y < ret.size.y; y++)
      for (int x = 0; x < ret.size.x; x++)
      {
        Vec2i pos(x, y);
        ret.SetValue(pos, lhs - rhs.GetValue(pos));
      }
    return ret;
  }

  friend NoiseMap Pow(NoiseMap const &lhs, NoiseMap const &rhs)
  {
    NoiseMap ret = FromIntersection(lhs, rhs);
    for (int y = 0; y < ret.size.y; y++)
      for (int x = 0; x < ret.size.x; x++)
      {
        Vec2i pos(x, y);
        ret.SetValue(pos, pow(lhs.GetValue(pos),rhs.GetValue(pos)));
      }
    return ret;
  }

  friend NoiseMap Pow(NoiseMap const &lhs, float rhs)
  {
    NoiseMap ret(lhs.size);
    for (int y = 0; y < ret.size.y; y++)
      for (int x = 0; x < ret.size.x; x++)
      {
        Vec2i pos(x, y);
        ret.SetValue(pos, pow(lhs.GetValue(pos), rhs));
      }
    return ret;
  }

};

struct PerlinNoiseGenerator
{
  static uint8_t RandomByte(int x);
  double Noise(double x, double y, int layer);
  NoiseMap GeneratePerlinNoise(int width, int height, int Layers);
  void SetSeed(uint16_t seed);
  uint16_t Seed();
private:
  uint16_t _seed = 1;
};

#endif // PerlinNoise_h__
