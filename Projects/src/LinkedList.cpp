#ifndef LinkedList_cpp__
#define LinkedList_cpp__

#include "LinkedList.h"
#include <assert.h>

template <typename T>
LinkedList<T>::LinkedList(int MaxItemCount)
{
  Initialize(MaxItemCount);
}

template <typename T>
void LinkedList<T>::Initialize(int MaxItemCount)
{
  ItemPool.Initialize(MaxItemCount);
  ItemList = new ListNode[MaxItemCount];
  ListStart = 0;
  ListEnd = 0;
  ItemCount = 0;
}

template <typename T>
int32_t LinkedList<T>::Insert(T item, int32_t itemPtr)
{
  if ((itemPtr > ItemCount) | (itemPtr < 0)) assert(false); // attempt to insert outside of list bounds

  uint32_t newNodePtr = ItemPool.New();
  ListNode& newNode = ItemList[newNodePtr];
  newNode.backPtr = ListStart;
  newNode.fwrdPtr = ListEnd;
  newNode.value = item;

  if (ItemCount == 0) // create new list from this item
  {
    ListEnd = ListStart = newNodePtr;
  }
  else if (itemPtr == 0) // Insert item at start of list
  {
    ItemList[ListStart].backPtr = newNodePtr;
    newNode.fwrdPtr = ListStart;
    ListStart = newNodePtr;
  }
  else if (itemPtr == ItemCount) // Insert item at end of list
  {
    ItemList[ListEnd].fwrdPtr = newNodePtr;
    newNode.backPtr = ListEnd;
    ListEnd = newNodePtr;
  }
  else // Insert item into the middle of the list
  {
    //How will we do that?
  }

  ItemCount++;

  return newNodePtr;

}

template <typename T>
T LinkedList<T>::Obtain(int32_t itemPtr)
{
  return ItemList[itemPtr].value;
}

template <typename T>
void LinkedList<T>::MoveToStart(int32_t itemPtr)
{
  if (itemPtr != ListStart)
  {
    ListNode& first = ItemList[itemPtr];
    first.fwrdPtr = ListStart;
    ListStart = itemPtr;
  }
}

template <typename T>
void LinkedList<T>::Delete(int32_t itemPtr)
{
  if ((itemPtr > ItemCount) | (itemPtr < 0)) assert(false); // attempt to delete outside of list bounds

  ListNode& oldNode = ItemList[itemPtr];

  if (itemPtr == ListStart) // Update start of list
    ListStart = oldNode.fwrdPtr;
  else // Fix item node before this one
    ItemList[oldNode.backPtr].fwrdPtr = oldNode.fwrdPtr;

  if (itemPtr == ListEnd) // Update end of list
    ListEnd = oldNode.backPtr;
  else // Fix item node after this one
    ItemList[oldNode.fwrdPtr].backPtr = oldNode.backPtr;

  ItemPool.Old(itemPtr);
}

template <typename T>
int32_t LinkedList<T>::FirstItem()
{
  return ListStart;
}

template <typename T>
int32_t LinkedList<T>::FinalItem()
{
  return ListEnd;
}

template <typename T>
int32_t LinkedList<T>::NextItem(int32_t itemPtr)
{
  return ItemList[itemPtr].fwrdPtr;
}

template <typename T>
int32_t LinkedList<T>::PrevItem(int32_t itemPtr)
{
  return ItemList[itemPtr].backPtr;
}

#endif // LinkedList_cpp__
