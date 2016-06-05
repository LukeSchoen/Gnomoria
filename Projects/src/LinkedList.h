#ifndef LinkedList_h__
#define LinkedList_h__

#include <stdint.h>
#include "Pool.h"

template <typename T>
struct LinkListNode
{
  T value;
  int32_t fwrdPtr;
  int32_t backPtr;
};


template <typename T>
struct LinkedList
{
  LinkedList(int MaxItemCount = 0);

  void Initialize(int MaxItemCount);

  int32_t Insert(T item, int32_t itemPtr);

  T Obtain(int32_t itemPtr);

  void MoveToStart(int32_t itemPtr);

  void Delete (int32_t itemPtr);

  int32_t FirstItem();

  int32_t FinalItem();

  int32_t NextItem(int32_t itemPtr);

  int32_t PrevItem(int32_t itemPtr);

private:

  typedef LinkListNode<T> ListNode;

  int32_t ListStart = 0;

  int32_t ListEnd = 0;

  int32_t ItemCount = 0;

  ListNode* ItemList;

  Pool ItemPool;
};

//Implementation
#include "LinkedList.cpp"

#endif // LinkedList_h__
