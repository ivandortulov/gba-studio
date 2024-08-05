#pragma once

#include <cstdlib>
#include <cstring>
#include <gba_console.h>

#include "../util/log.hpp"

#define MAKE_RES_ID(Type, Count) \
    ((Type) << 28) | ((Count) & 0x0FFFFFFF)

#define RES_ID(Id) \
    (Id) & 0x0FFFFFFF

#define RES_TYPE(Id) \
    (Types::EResourceType)((Id) >> 28)

#ifdef _MSC_VER
#  define PACKED
#  define UNPACKED 
#else
#  define PACKED __attribute__((packed))
#  define UNPACKED
#endif

#ifdef _DEBUG
#  define ASSERT(condition, message) \
        do { \
            if (!(condition)) { \
                consoleDemoInit(); \
                iprintf("ASSERT %s\nFILE:%s\nFUNC:%s\nLINE:%u\nMSG:%s\n", #condition, __FILE__ , __func__ , __LINE__, message); \
                LOG_ERR("Assertion %s failed in %s (%s:%u): %s", #condition, __FILE__, __func__, __LINE__, message); \
                std::abort(); \
            } \
        } while (false)
#else
#  define ASSERT
#endif

#define ASSERT_FALSE(condition, message) \
    ASSERT(!(condition), message)

#define ASSERT_TRUE(condition, message) \
    ASSERT(condition, message)

#define ASSERT_EQ(expected, actual, message) \
    ASSERT((expected) == (actual), message)


//extern void* operator new(size_t size, const char* file, int line);
//extern void* operator new[](size_t size, const char* file, int line);
//extern void operator delete(void* ptr) noexcept;
//extern void operator delete[](void* ptr) noexcept;
