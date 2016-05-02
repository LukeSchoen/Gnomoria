#define gmAlloc(size) malloc(size)

#define gmAllocZero(size) calloc(size)

#define gmAllocType(type, count) gmAlloc(count * sizeof(type))

#define gmAllocTypeZero(type, count) gmAllocZero(count * sizeof(type))

#define gmRealloc(ptr, size) realloc(ptr, size)

#define gmReallocType(ptr, count) (decltype(ptr))gmRealloc(ptr, count * sizeof(*ptr))

#define gmFree(ptr) free(ptr); ptr = nullptr

#define gmCopy(target, source, size) memcpy(target, source, size)

#define gmCopyType(target, source, count) memcpy(target, source, sizeof(*source) * count)