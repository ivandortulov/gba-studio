#include "engine.hpp"

#include <gba_console.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "gba_pack.hpp"
#include "resource_loader.hpp"
#include "resource_loader_palette.hpp"
#include "resource_loader_tile_set.hpp"
#include "resource_loader_tile_map.hpp"
#include "resource_loader_scene.hpp"

#define ROM_START 0x08000000
#define ROM_END   0x09FFFFFF

namespace GBS {
    Engine::Engine(const u8* pckData, const u32 pckSize) {
        if (!GBAPack::getInstance()->loadFromMemory(pckData, pckSize)) {
            consoleDemoInit();
            iprintf("Failed to load game pack!");
        }

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