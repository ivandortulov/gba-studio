#pragma once

#include "reference.hpp"
#include "resource.hpp"

#include <map>
#include <string>

namespace GBS {
    class GBAPack;

    class ResourceManager {
    public:
        static ResourceManager* getInstance() {
            if (instance == nullptr) {
                instance = new ResourceManager();
            }
            return instance;
        }

    public:
        void allocatePalette(u32 paletteId);
        u32 allocateTileSet(u32 tileSetId);
        u32 allocateTileMap(u32 tileMapId);

        void free(u32 resourceId);

    private:
        ResourceManager();

    private:
        static ResourceManager* instance;

        u32 loadedPalette;
        std::map<u32, u8> loadedTileSets;   // TileSet ID -> Block ID
        std::map<u32, u8> loadedTileMaps;   // TileMap ID -> Block ID
    };
}