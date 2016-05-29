#ifndef LinkedList_h__
#define LinkedList_h__


struct MemoryPool
{
  MemoryPool(int ItemByteSize, int MaxItemCount);

  void* New();

  void Old(void* oldData);

private:
  int itemSize;

  int itemCount;

  int currentItem = 0;

  char** EmptyList;

  char* dataPool;
};



#endif // LinkedList_h__
