#include "log.hpp"

#include <gba_types.h>

#include <cstdarg>
#include <cstdio>

#define REG_DEBUG_ENABLE (volatile uint16_t *)0x4FFF780
#define REG_DEBUG_FLAGS (volatile uint16_t *)0x4FFF700
#define REG_DEBUG_STRING (char *)0x4FFF600

namespace GBS {
        static Logger sLogger;

        // static void mgbaPrintf(ELogLevel level, const char* ptr, ...) {
        //     va_list args;
        //     va_start(args, ptr);
        //     vsprintf(REG_DEBUG_STRING, ptr, args);
        //     va_end(args);
        //     *REG_DEBUG_FLAGS = ((int)level & 0x7) | 0x100;
        // }

        // static u8 mgbaOpen() {
        //     *REG_DEBUG_ENABLE = 0xC0DE;
        //     return *REG_DEBUG_ENABLE == 0x1DEA;
        // }

        // static void mgbaClose() {
        //     *REG_DEBUG_ENABLE = 0;
        // }

        Logger::Logger() {
#ifndef _MSC_VER
                * REG_DEBUG_ENABLE = 0xC0DE;
#endif
        }

        Logger::~Logger() {
#ifndef _MSC_VER
                * REG_DEBUG_ENABLE = 0;
#endif
        }

        void Logger::log(ELogLevel level, const char* ptr, ...) {
                va_list args;
                va_start(args, ptr);
#ifndef _MSC_VER
                vsprintf(REG_DEBUG_STRING, ptr, args);
#endif
                va_end(args);
#ifndef _MSC_VER
                * REG_DEBUG_FLAGS = ((int)level & 0x7) | 0x100;
#endif
        }
}