#pragma once

#include <cstdlib>

#define MAKE_RES_ID(Type, Count) \
    ((Type) << 28) | ((Count) & 0x0FFFFFFF)

#define RES_ID(Id) \
    (Id) & 0x0FFFFFFF

#define RES_TYPE(Id) \
    ((Id) >> 28)

#ifdef _MSC_VER
#  define PACKED
#  define UNPACKED 
#else
#  define PACKED __attribute__((packed))
#  define UNPACKED
#endif

//extern void* operator new(size_t size, const char* file, int line);
//extern void* operator new[](size_t size, const char* file, int line);
//extern void operator delete(void* ptr) noexcept;
//extern void operator delete[](void* ptr) noexcept;
