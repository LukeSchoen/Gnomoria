#include "MemoryPool.h"
#include <assert.h>

MemoryPool::MemoryPool(int ItemByteSize, int MaxItemCount)
{
  itemSize = ItemByteSize;
  itemCount = MaxItemCount;
  EmptyList = new char*[MaxItemCount];
  dataPool = new char[ItemByteSize * MaxItemCount];
  for (int i = 0; i < itemCount; i++)
  {
    EmptyList[i] = dataPool + i * itemSize;
  }
}

void* MemoryPool::New()
{
  if (currentItem == itemCount) assert(false); // Ran out of memory!
  return EmptyList[currentItem++];
}

void MemoryPool::Old(void* oldData)
{
  EmptyList[currentItem--] = (char*)oldData;
}
