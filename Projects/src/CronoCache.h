#ifndef CronoCache_h__
#define CronoCache_h__

#include <stdint.h>
#include "Math/Vector.h"
#include "DenseHashmap.h"


struct DenseHashMap;

struct cacheNode;


struct CronoCache
{
public:

  CronoCache(int CacheSize = 512);

  int GetDataAddress(int64_t hash, bool &dataIsCached);
  
private:

  uint32_t listStart = 0;

  uint32_t listEnd = 0;

  uint32_t CurrentItemCount = 0;

  uint32_t MaxItemCount = 0;

  cacheNode *nodeList;

  DenseHashMap nodeLookup;

};

#endif // CronoCache_h__
