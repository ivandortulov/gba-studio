#include "resource_loader_tile_set.hpp"

#include "tile_set.hpp"
#include "macros.hpp"
#include "gba_pack.hpp"
#include "palette.hpp"
#include "log.hpp"
#include "renderer.hpp"
#include <memory.h>

namespace GBS {
    ResourceLoaderTileSet* ResourceLoaderTileSet::instance = nullptr;

    struct PACKED TileSetHeader {
        u32 paletteId;
        u16 numTiles;
    };

    RefPointer<Resource> ResourceLoaderTileSet::loadInternal(u32 id) {
        const u8* data = nullptr;
        u32 dataSize;
        u32 resourceId = MAKE_RES_ID(Types::TileSet, id);

        GBAPack::getInstance()->getResourceData(
            resourceId,
            data,
            dataSize
        );

        if (data == nullptr) {
            LOG_ERR("Failed to load tile set resource with id %d", id);
            return RefPointer<TileSet>();
        }

        u32 offset = 0;
        TileSetHeader header = { 0 };
        memcpy(&header, data, sizeof(TileSetHeader));
        offset += sizeof(TileSetHeader);

        RefPointer<Palette> palette =
            ResourceLoader::load(Types::Palette, RES_ID(header.paletteId));

        if (palette.isNull() || !palette->isValid()) {
            LOG_ERR("Failed to load palette!");
            return RefPointer<TileSet>();
        }

        TileSet* result = new TileSet();

        u8 blockId = Renderer::getInstance()->allocateTileSet(resourceId);
        if (blockId != 255) {
            result->blockId = blockId;
            result->palette = palette;
            Renderer::getInstance()->loadTileSet(blockId, data + offset, dataSize - offset);
        }

        return RefPointer<TileSet>(result);
    }
}