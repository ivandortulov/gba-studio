#include "engine.hpp"

#ifndef _MSC_VER
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "../resources/gba_pack.hpp"
#include "../resources/resource_loader.hpp"
#include "../resources/resource_loader_palette.hpp"
#include "../resources/resource_loader_tile_set.hpp"
#include "../resources/resource_loader_tile_map.hpp"
#include "../resources/resource_loader_scene.hpp"

#include "../scene_tree/scene_tree.hpp"

#define ROM_START 0x08000000
#define ROM_END   0x09FFFFFF

namespace GBS {
    Engine::Engine(const u8* pckData, const u32 pckSize) {
        ResourceLoader::registerLoader(
            Types::Palette,
            ResourceLoaderPalette::getSingleton()
        );
        ResourceLoader::registerLoader(
            Types::TileSet,
            ResourceLoaderTileSet::getSingleton()
        );
        ResourceLoader::registerLoader(
            Types::TileMap,
            ResourceLoaderTileMap::getSingleton()
        );
        ResourceLoader::registerLoader(
            Types::Scene,
            ResourceLoaderScene::getSingleton()
        );

        bool result = GBAPack::getInstance()->loadFromMemory(pckData, pckSize);
        ASSERT_TRUE(result, "There was a problem loading the game pack");

        if (!result) {
            return;
        }

#ifndef _MSC_VER
        irqInit();
        irqEnable(IRQ_VBLANK);
#endif

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
#ifndef _MSC_VER
            VBlankIntrWait();
#endif

            SceneTree::getInstance()->iteration();
        }

        return 0;
    }
}