#include "Pool.h"
#include <assert.h>


Pool::Pool(uint32_t MaxItemCount)
{
  Initialize(MaxItemCount);
}

void Pool::Initialize(uint32_t MaxItemCount)
{
  currentItem = 0;
  maxItemCount = MaxItemCount;
  freeList = new uint32_t[MaxItemCount];
  for (uint32_t i = 0; i < MaxItemCount; i++)
    freeList[i] = i;
}

uint32_t Pool::New()
{
  if (currentItem >= maxItemCount) assert(false); // Pool is empty!
  return freeList[currentItem++];
}

void Pool::Old(uint32_t val)
{
  if (currentItem <= 0) assert(false); // Pool is over-filled!
  freeList[--currentItem] = val;
}

