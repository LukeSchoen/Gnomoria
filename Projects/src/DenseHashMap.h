#ifndef DenseHashMap_h__
#define DenseHashMap_h__

#include <stdint.h>
#include "Math/Vector.h"

struct HashPair;

struct DenseHashMap
{
public:
  DenseHashMap(int maxKeyCount = 512);
  void Insert(int64_t key, int64_t val);
  bool Obtain(int64_t key, int64_t &val);
  void Delete(int64_t key);
private:
  uint16_t Hash(int64_t key);
  HashPair* mapNodes;
  int* freeNodes;
  int freeNodeCount;
  static const int bucketCount = 65536;
  int buckets[bucketCount];
};

#endif // DenseHashMap_h__
