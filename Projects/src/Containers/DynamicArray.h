#include "GMemory.h"
#include <algorithm>

namespace gm
{
  template<typename T, size_t reallocationSize = 0>
  struct DynamicArray
  {

    DynamicArray(size_t initialCapacity = 0)
      : length(0)
      , capacity(0)
      , data(nullptr)
    {
      Resize(initialCapacity);
    }

    template <size_t otherAllocationSize>
    DynamicArray(DynamicArray<T, otherAllocationSize> const &other)
      : length(0)
      , capacity(0)
      , data(nullptr)
    {
      *this = other;
    }

    void Resize(size_t newCapacity)
    {
      capacity = std::max(capacity, newCapacity);
      data = gmReallocType(data, capacity);
    }

    size_t Length() const
    {
      return length;
    }

    T &PushBack(T&& value)
    {
      if (length + 1 > capacity)
        Resize(OverFlowSize());
      data[length] = value;
      return data[length++];
    }

    T &PushBack(T const &value)
    {
      if (length + 1 > capacity)
        Resize(OverFlowSize());
      data[length] = value;
      return data[length++]
    }

    T &operator[](size_t index) { return data[index]; }

    T const &operator[](size_t index) const { return data[index]; }

    ~DynamicArray()
    {
      Clear();
      gmFree(data);
      capacity = 0;
    }

    void Clear()
    {
      for (size_t i = 0; i < length; i++)
        data[i].~T();
      length = 0;
    }

    size_t ShrinkToLength()
    {
      if (capacity > length)
      {
        T* newData = gmAllocType(T, length);
        gmCopyType(newData, data, length);
        gmFree(data);
        data = newData;
        capacity = length;
      }
    }

    template<size_t otherAllocationSize>
    DynamicArray<T, reallocationSize> &operator=(DynamicArray<T, otherAllocationSize> const &other)
    {
      Clear();
      length = other.Length();
      Resize(length);
      for (size_t i = 0; i < length; i++)
        data[i] = other.data[i];
    }

    template<size_t otherAllocationSize>
    DynamicArray<T, reallocationSize> &operator=(DynamicArray<T, otherAllocationSize>&& other)
    {
      Clear();
      gmFree(data);

      length = other.length;
      capacity = other.capacity;
      data = other.data;

      other.length = 0;
      other.capacity = 0;
      other.data = nullptr;
    }

  private:
    T* data;
    size_t length;
    size_t capacity;

    size_t OverFlowSize()
    {
      if (reallocationSize == 0)
        return capacity * 2 + 1;
      else
        return capacity + reallocationSize;
    }
  };
}

