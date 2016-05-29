#ifndef ChronoCache_h__
#define ChronoCache_h__

#include <stdint.h>
#include "Math/Vector.h"
#include "DenseHashmap.h"
#include "LinkedList.h"

struct ChronoCache
{
public:

  ChronoCache(int CacheSize = 0);

  int GetDataAddress(int64_t hash, bool &dataIsCached);
  
private:

  uint32_t CurrentItemCount = 0;

  uint32_t MaxItemCount = 0;

  LinkedList<int64_t> nodeList;

  DenseHashMap nodeLookup;

};

#endif // ChronoCache_h__
