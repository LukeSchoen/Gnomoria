#include "ChronoCache.h"
#include "Transforms.h"
#include <assert.h>


ChronoCache::ChronoCache(int CacheSize)
{
  MaxItemCount = CacheSize;
  nodeList.Initialie(CacheSize);
}

int ChronoCache::GetDataAddress(int64_t hash, bool &isLoaded)
{
  int64_t nodeID;
  if (nodeLookup.Obtain(hash, nodeID)) // data already in the cache?
  {
    isLoaded = true;
    nodeList.Move(nodeID, nodeList.FirstItem()); // move this back to the start
    return nodeID;
  }
  else // data needs to be loaded
  {
    isLoaded = false;
    if(CurrentItemCount < MaxItemCount) // empty spot available
    {
      return nodeList.Insert(hash, nodeList.FirstItem());
    }
    else // no free spots available so we replace an old entry
    {
      nodeList.Delete(nodeList.FinalItem());
      return nodeList.Insert(hash, nodeList.FirstItem());
    }
  }
}
