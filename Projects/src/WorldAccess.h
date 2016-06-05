#ifndef WorldAccess_h__
#define WorldAccess_h__
#include "Math\Vector.h"
#include "block.h"

struct WorldAccess
{
public:
  static WorldAccess *GetInstance();
  
  void Save(char* folderPath);
  void Load(char* folderPath);

  Block GetBlock(Vec3i BlockWorldPos);
  void SetBlock(Vec3i BlockWorldPos, Block newBlock);

  Vec3i GetSize();

private:
  bool Loaded = false;
  char* worldFilePath = nullptr;
  Vec3i worldSize;

};
#endif WorldAccess_h__