#include "engine.hpp"

#include <gba_console.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "gba_pack.hpp"

#define ROM_START 0x08000000
#define ROM_END   0x09FFFFFF

namespace GBS {
    Engine::Engine(const u8* pckData, const u32 pckSize) {
        if (!GBAPack::getInstance()->loadFromMemory(pckData, pckSize)) {
            consoleDemoInit();
            iprintf("Failed to load game pack!");   
        }

        isInitialized = true;
    }

    Engine::~Engine() {
        delete GBAPack::getInstance();
    }

    int Engine::run() {
        if (!isInitialized) {
            return -1;
        }

        while (1) {

        }

        return 0;
    }
}