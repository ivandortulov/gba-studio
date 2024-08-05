#include "renderer.hpp"

#ifndef _MSC_VER
# include <gba_video.h>
# include <gba_dma.h>
#endif

#include "../util/log.hpp"


namespace GBS {
    Renderer* Renderer::instance = nullptr;

    Renderer::Renderer()
        : freeTileSetBlocks({ 0, 1, 2, 3 })
        , freeTileMapBlocks({ 28, 29, 30, 31 }) {
    }

    u8 Renderer::allocateTileSet(const u32 tileSetId) {
        if (freeTileSetBlocks.empty()) {
            LOG_WARN("All tile set blocks are occupied!");
            return 255;
        }

        u8 blockId = freeTileSetBlocks.front();
        freeTileSetBlocks.pop_front();

        loadedTileSets[tileSetId] = blockId;

        return blockId;
    }

    u8 Renderer::allocateTileMap(const u32 tileMapId) {
        if (freeTileMapBlocks.empty()) {
            LOG_WARN("All tile map blocks are occupied!");
            return 255;
        }

        u8 blockId = freeTileMapBlocks.front();
        freeTileMapBlocks.pop_front();

        loadedTileMaps[tileMapId] = blockId;

        return blockId;
    }

    void Renderer::loadPalette(
        const u8* data,
        const u32 dataSize,
        bool background
    ) {
#ifndef _MSC_VER
        DMA3COPY(
            data,
            BG_PALETTE,
            dataSize / 2
        );
#endif
    }

    void Renderer::loadTileSet(
        const u8 blockId,
        const u8* data,
        const u32 dataSize
    ) {
#ifndef _MSC_VER
        DMA3COPY(
            data,
            TILE_BASE_ADR(blockId),
            dataSize / 2
        );
#endif
    }

    void Renderer::loadTileMap(
        const u32 tileSetId,
        const Types::EBackground background,
        const u8 blockId,
        const u8* data,
        const u32 dataSize
    ) {
#ifndef _MSC_VER
        switch (background) {
        case Types::Background0: {
            REG_BG0CNT =
                BG_256_COLOR
                | BG_SIZE_0
                | BG_TILE_BASE(loadedTileSets[tileSetId])
                | BG_MAP_BASE(blockId);

            REG_BG0HOFS = 0;
            REG_BG0VOFS = 0;
        }
                               break;

        case Types::Background1: {
            REG_BG1CNT =
                BG_256_COLOR
                | BG_SIZE_0
                | BG_TILE_BASE(loadedTileSets[tileSetId])
                | BG_MAP_BASE(blockId);

            REG_BG1HOFS = 0;
            REG_BG1VOFS = 0;
        }
                               break;

        case Types::Background2: {
            REG_BG2CNT =
                BG_256_COLOR
                | BG_SIZE_0
                | BG_TILE_BASE(loadedTileSets[tileSetId])
                | BG_MAP_BASE(blockId);

            REG_BG2HOFS = 0;
            REG_BG2VOFS = 0;
        }
                               break;

        case Types::Background3: {
            REG_BG3CNT =
                BG_256_COLOR
                | BG_SIZE_0
                | BG_TILE_BASE(loadedTileSets[tileSetId])
                | BG_MAP_BASE(blockId);

            REG_BG3HOFS = 0;
            REG_BG3VOFS = 0;
        }
                               break;
        }

        DMA3COPY(
            data,
            MAP_BASE_ADR(blockId),
            dataSize
        );
#endif
    }
}