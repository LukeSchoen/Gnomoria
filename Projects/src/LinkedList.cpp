#include "LinkedList.h"
#include <assert.h>

template <typename T>
struct ListNode
{
  T value;
  int32_t fwrdPtr;
  int32_t backPtr;
};

template <typename T>
LinkedList::LinkedList(int MaxItemCount)
{
  Initialie(MaxItemCount);
}

template <typename T>
void LinkedList::Initialie(int MaxItemCount)
{
  ItemPool.Initialize(MaxItemCount);
  ItemList = new ListNode[MaxItemCount];
  ListStart = -1;
  ListEnd = -1;
  ItemCount = 0;
}

template <typename T>
int32_t LinkedList::Insert(T item, int32_t itemPtr)
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

  return newNodePtr;

}

template <typename T>
T LinkedList::Obtain(int32_t itemPtr)
{
  return ItemList[itemPtr].value;
}

template <typename T>
void LinkedList::Move(int32_t sourceItemPtr, int32_t destinationItemPtr)
{
  if (sourceItemPtr != destinationItemPtr)
  {
    T sourceData = Obtain(sourceItemPtr);
    Delete(sourceItemPtr);
    Insert(sourceData, destinationItemPtr);
  }
}

template <typename T>
void LinkedList::Delete(int32_t itemPtr)
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
int32_t LinkedList::FirstItem()
{
  return ListStart;
}

template <typename T>
int32_t LinkedList::FinalItem()
{
  return ListEnd;
}

template <typename T>
int32_t LinkedList::NextItem(int32_t itemPtr)
{
  return ItemList[itemPtr].fwrdPtr;
}

template <typename T>
int32_t LinkedList::PrevItem(int32_t itemPtr)
{
  return ItemList[itemPtr].backPtr;
}
