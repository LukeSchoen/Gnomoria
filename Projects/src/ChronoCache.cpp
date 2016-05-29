#include "ChronoCache.h"
#include "Transforms.h"
#include <assert.h>

struct cacheNode
{
  uint32_t cacheLoc;
  uint32_t backPtr;
  uint32_t fwrdPtr;
  int64_t hash;
};

ChronoCache::ChronoCache(int CacheSize)
{
  MaxItemCount = CacheSize;
  nodeList = new cacheNode[CacheSize];
}

int ChronoCache::GetDataAddress(int64_t hash, bool &isLoaded)
{
  // Is the data already in the cache?
  int64_t nodeID;
  if (nodeLookup.Obtain(hash, nodeID))
  {
    isLoaded = true;
    // if this node is not the head then make it the head
    if (nodeID != listStart && false)
    {
      cacheNode &current = nodeList[nodeID];
      cacheNode &next = nodeList[current.fwrdPtr];
      cacheNode &previous = nodeList[current.fwrdPtr];
      previous.fwrdPtr = current.fwrdPtr;
      if (nodeID != listEnd) next.backPtr = current.backPtr;
      cacheNode &first = nodeList[listStart];
      current.fwrdPtr = listStart;
      listStart = nodeID;
      current.backPtr = listStart;
      first.backPtr = listStart;
    }
    return nodeList[nodeID].cacheLoc;
  }
  else
  {
    isLoaded = false;
    if (CurrentItemCount < MaxItemCount)
    { // Filling up cache for the first time
      if (CurrentItemCount > 0)
      {
        uint32_t secondPtr = listStart;
        listStart = MaxItemCount - (1 + CurrentItemCount);
        cacheNode &first = nodeList[listStart];
        cacheNode &second = nodeList[secondPtr];
        first.hash = hash;
        first.fwrdPtr = secondPtr;
        first.backPtr = listStart;
        first.cacheLoc = CurrentItemCount;
        second.backPtr = listStart;
        nodeLookup.Insert(hash, listStart);
        CurrentItemCount++;
        return first.cacheLoc;
      }
      else
      {
        listStart = MaxItemCount - 1;
        cacheNode &first = nodeList[listStart];
        listEnd = listStart;
        first.hash = hash;
        first.fwrdPtr = listEnd;
        first.backPtr = listStart;
        first.cacheLoc = CurrentItemCount;
        nodeLookup.Insert(hash, listStart);
        CurrentItemCount++;
        return first.cacheLoc;
      }
    }
    else
    { // the cache has filled up so we are replacing old cached data
      cacheNode &last = nodeList[listEnd];
      cacheNode &secondLast = nodeList[last.backPtr];
      uint32_t newStart = listEnd;
      nodeLookup.Delete(last.hash);
      // remove this node from list
      listEnd = last.backPtr;
      secondLast.fwrdPtr = listEnd;
      // add him back at the start
      cacheNode &first = last;
      first.hash = hash;
      first.fwrdPtr = listStart;
      listStart = newStart;
      return first.cacheLoc;
    }
    return 0;
  }
}
