#ifndef LinkedList_h__
#define LinkedList_h__

#include <stdint.h>
#include "Pool.h"

template <typename T>
struct ListNode;

template <typename T>
struct LinkedList
{
  LinkedList(int MaxItemCount = 0);

  void Initialie(int MaxItemCount);

  int32_t Insert(T item, int32_t itemPtr);

  T Obtain(int32_t itemPtr);

  void Move(int32_t sourceItemPtr, int32_t destinationItemPtr);

  void Delete (int32_t itemPtr);

  int32_t FirstItem();

  int32_t FinalItem();

  int32_t NextItem(int32_t itemPtr);

  int32_t PrevItem(int32_t itemPtr);

private:

  int32_t ListStart = -1;

  int32_t ListEnd = -1;

  int32_t ItemCount = 0;

  ListNode* ItemList;

  Pool ItemPool;
};

#endif // LinkedList_h__
