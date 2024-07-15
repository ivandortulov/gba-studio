#include "engine.hpp"

#include <gba_console.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>

#define ROM_START 0x08000000
#define ROM_END   0x09FFFFFF

namespace GBS {
    static void _fail(const char* msg) {
        consoleDemoInit();
        iprintf("%s\n", msg);
        assert(false);
    }

    Engine::Engine(const u8* pckData, const u32 pckSize) {
        pack = new GBAPack();
        if (!pack->loadFromMemory(pckData, pckSize)) {
            _fail("Failed to load asset pack!");
            return;
        }

        resourceManager = new ResourceManager(pack);
        sceneTree = new SceneTree(resourceManager, renderer);

        isInitialized = true;
    }

    Engine::~Engine() {
        delete[] pack;
    }

    void Engine::tick() {
        if (!isInitialized) {
            return;
        }
    }
}