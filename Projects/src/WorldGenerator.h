#ifndef WorldGenerator_h__
#define WorldGenerator_h__

#include "WorldAccess.h"

void testworldgen();

struct WorldGenerator
{
public:
  void Create(char* folderPath, Vec3i Size);

  static WorldGenerator *GetInstance();

  void GenerateWorld();

private:
  bool Loaded = false;
  char* worldFilePath = nullptr;

};
#endif WorldGenerator_h__