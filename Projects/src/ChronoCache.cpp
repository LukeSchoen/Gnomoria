#include "ChronoCache.h"
#include "Transforms.h"
#include <assert.h>


ChronoCache::ChronoCache(int CacheSize)
{
  MaxItemCount = CacheSize;
  nodeList.Initialize(CacheSize);
}

int ChronoCache::GetDataAddress(int64_t hash, bool &isLoaded)
{
  int64_t nodeID;
  if (nodeLookup.Obtain(hash, nodeID)) // data already in the cache?
  {
    isLoaded = true;
    nodeList.MoveToStart(nodeID);
    return nodeID;
  }
  else // data needs to be loaded!
  {
    isLoaded = false;
    if(CurrentItemCount < MaxItemCount) // empty spot available
    {
      CurrentItemCount++;
      uint32_t newNodeID = nodeList.Insert(hash, nodeList.FirstItem());
      nodeLookup.Insert(hash, newNodeID);
      return newNodeID;
    }
    else // no free spots available so we replace an old entry
    {
      nodeLookup.Delete(nodeList.Obtain(nodeList.FinalItem()));
      nodeList.Delete(nodeList.FinalItem());
      uint32_t newNodeID = nodeList.Insert(hash, nodeList.FirstItem());
      nodeLookup.Insert(hash, newNodeID);
      return newNodeID;
    }
  }
}
