#include "DenseHashMap.h"
#include <assert.h>

struct HashPair
{
  int64_t key;
  int64_t value;
  int fwrdPtr;
  int backPtr;
};

DenseHashMap::DenseHashMap(int maxKeyCount)
{
  if (maxKeyCount <= 0) assert(false); //Bad Key Count!
  mapNodes = new HashPair[maxKeyCount];
  freeNodes = new int[maxKeyCount];
  freeNodeCount = maxKeyCount;
  for (int nodeID = 0; nodeID < maxKeyCount; nodeID++)
    freeNodes[nodeID] = maxKeyCount-nodeID-1;
  for (int bucketID = 0; bucketID < bucketCount; bucketID++)
    buckets[bucketID] = -1;
}


uint16_t DenseHashMap::Hash(int64_t key)
{
  //This would probably work better
  //return (key * 11400714819323198549ul) >> (64 - 16);
  
  key = ((key >> 32) & 0xFFFFFFFF) ^ ((key)& 0xFFFFFFFF);
  return ((key >> 16) & 0xFFFF) ^ (key & 0xFFFF);
}


void DenseHashMap::Insert(int64_t key, int64_t val)
{
  uint16_t hash = Hash(key);
  int firstNodeInBucket = buckets[hash];

  int nextFreeNode = freeNodes[--freeNodeCount];
  assert(freeNodeCount >= 0); //Added too many keys!
  buckets[hash] = nextFreeNode;
  HashPair &NewNodn = mapNodes[nextFreeNode];
  NewNodn.key = key;
  NewNodn.value = val;
  NewNodn.backPtr = -1;

  if (firstNodeInBucket == -1)
  {//Create new bucket
    NewNodn.fwrdPtr = -1;
  }
  else
  {//Add to another bucket
    NewNodn.fwrdPtr = firstNodeInBucket;
    HashPair &node = mapNodes[firstNodeInBucket];
    node.backPtr = nextFreeNode;
  }
}


bool DenseHashMap::Obtain(int64_t key, int64_t &val)
{
  uint16_t hash = Hash(key);
  int firstNodeInBucket = buckets[hash];
  if (firstNodeInBucket == -1)
  {//The key does not exist in the HashMap
    return false;
  }
  else
  {//Check if the key is in this bucket
    while (true)
    {
      HashPair &node = mapNodes[firstNodeInBucket];
      if (node.key == key)
      {//Found him!
        val = node.value;
        return true;
      }
      else
      {
        if (node.fwrdPtr == -1)
        {//Reached the end of the bucket, and no pair with this key was found!
          return false;
        }
        else
        {//Keep looking threw the bucket
          firstNodeInBucket = node.fwrdPtr;
        }
      }
    }
  }
}


void DenseHashMap::Delete(int64_t key)
{
  uint16_t hash = Hash(key);
  int firstNodeInBucket = buckets[hash];

  if (firstNodeInBucket == -1)
  {//The key does not exist in the HashMap
    return;
  }
  else
  {//Check if the key is in this bucket

    while (true)
    {
      HashPair &node = mapNodes[firstNodeInBucket];
      if (node.key == key)
      {
        //Found him!
        if (node.backPtr == -1) //Was he the owner of a slot?
          if (node.fwrdPtr == -1) //Does that slot now point to an empty bucket?
            buckets[hash] = -1; // If so free up the slot for someone else later
          else
            buckets[hash] = node.fwrdPtr; // assign it to the next node in the list

        //Remove him from his bucket
        HashPair &prevNode = mapNodes[node.backPtr];
        HashPair &nextNode = mapNodes[node.fwrdPtr];
        if (node.backPtr != -1) prevNode.fwrdPtr = node.fwrdPtr;
        if (node.fwrdPtr != -1) nextNode.backPtr = node.backPtr;

        //Return his memory to the node pool for later use
        freeNodes[freeNodeCount++] = firstNodeInBucket;
        return;
      }
      else
      {
        if (node.fwrdPtr == -1)
        {//Reached the end of the bucket, and no pair with this key was found!
          return;
        }
        else
        {//Keep looking threw the bucket
          firstNodeInBucket = node.fwrdPtr;
        }
      }
    }
  }
}
