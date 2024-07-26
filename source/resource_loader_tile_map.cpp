#include "resource_loader_tile_map.hpp"

#include "macros.hpp"
#include "gba_pack.hpp"
#include "tile_map.hpp"
#include "log.hpp"
#include "renderer.hpp"

#include <memory.h>

namespace GBS {
    struct PACKED TileMapHeader {
        u32 tileSetId;
        u16 width;
        u16 height;
        u16 background;
    };

    ResourceLoaderTileMap* ResourceLoaderTileMap::instance = nullptr;

    RefPointer<Resource> ResourceLoaderTileMap::loadInternal(u32 id) {
        const u8* data;
        u32 dataSize;
        u32 resourceId = MAKE_RES_ID(Types::TileMap, id);

        GBAPack::getInstance()->getResourceData(
            resourceId,
            data,
            dataSize
        );

        if (data == nullptr) {
            LOG_ERR("Failed to load tile map resource with id %d", id);
            return RefPointer<TileMap>();
        }

        u32 offset = 0;
        TileMapHeader header = { 0 };
        memcpy(&header, data, sizeof(TileMapHeader));
        offset += sizeof(TileMapHeader);

        RefPointer<TileSet> tileSet =
            ResourceLoader::load(Types::TileSet, RES_ID(header.tileSetId));

        if (tileSet.isNull() || !tileSet->isValid()) {
            LOG_ERR("Failed to load tile set!");
            return RefPointer<TileMap>();
        }

        TileMap* result
            = new TileMap();

        u8 blockId = Renderer::getInstance()->allocateTileMap(resourceId);
        if (blockId != 255) {
            result->blockId = blockId;
            result->tileSet = tileSet;
            Renderer::getInstance()->loadTileMap(
                header.tileSetId,
                (Types::EBackground)header.background,
                blockId,
                data + offset,
                dataSize - offset
            );
        }

        return RefPointer<TileMap>(result);
    }
}