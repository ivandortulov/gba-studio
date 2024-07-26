#pragma once

#include <gba_types.h>

#include "types.hpp"
#include "tile_set.hpp"

#include <deque>
#include <map>

#define ERR_GENERIC_FAILURE -1

namespace GBS {
    class Renderer {
    public:
        inline static Renderer* getInstance() {
            if (instance == nullptr) {
                instance = new Renderer();
            }

            return instance;
        }

    public:
        u8 allocateTileSet(const u32 tileSetId);
        u8 allocateTileMap(const u32 tileMapId);

        void loadPalette(
            const u8* data,
            const u32 dataSize,
            bool background
        );

        void loadTileSet(
            const u8 blockId,
            const u8* data,
            const u32 dataSize
        );

        void loadTileMap(
            const u32 tileSetId,
            const Types::EBackground background,
            const u8 blockId,
            const u8* data,
            const u32 dataSize
        );

        void free(u32 resourceId);

    private:
        Renderer();

    private:
        std::deque<u8> freeTileSetBlocks;
        std::deque<u8> freeTileMapBlocks;
        std::map<u32, u8> loadedTileSets;   // TileSet ID -> Block ID
        std::map<u32, u8> loadedTileMaps;   // TileMap ID -> Block ID

        static Renderer* instance;
    };
}