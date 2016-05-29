#ifndef Pool_h__
#define Pool_h__

#include "stdint.h"

struct Pool
{
  Pool(uint32_t ItemMaxCount = 0);

  void Initialize(uint32_t ItemMaxCount);

  uint32_t New();

  void Old(uint32_t val);

private:

  uint32_t maxItemCount = 0;

  uint32_t currentItem = 0;

  uint32_t* freeList;
};

#endif // Pool_h__
