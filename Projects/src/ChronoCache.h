#ifndef ChronoCache_h__
#define ChronoCache_h__

#include <stdint.h>
#include "Math/Vector.h"
#include "DenseHashmap.h"


struct DenseHashMap;

struct cacheNode;


struct ChronoCache
{
public:

  ChronoCache(int CacheSize = 512);

  int GetDataAddress(int64_t hash, bool &dataIsCached);
  
private:

  uint32_t listStart = 0;

  uint32_t listEnd = 0;

  uint32_t CurrentItemCount = 0;

  uint32_t MaxItemCount = 0;

  cacheNode *nodeList;

  DenseHashMap nodeLookup;

};

#endif // ChronoCache_h__
