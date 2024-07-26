#include "resource_loader_scene.hpp"
#include "gba_pack.hpp"
#include "types.hpp"
#include "log.hpp"
#include "macros.hpp"
#include "packed_scene.hpp"

namespace GBS {
    ResourceLoaderScene* ResourceLoaderScene::instance = nullptr;

    RefPointer<Resource> ResourceLoaderScene::loadInternal(u32 id) {
        const u8* data;
        u32 dataSize;

        GBAPack::getInstance()->getResourceData(
            MAKE_RES_ID(Types::Scene, id),
            data,
            dataSize
        );

        if (data == nullptr) {
            LOG_ERR("Failed to load scene resource with id %d", id);
            return RefPointer<PackedScene>();
        }

        u32 offset = 0;
        u32 value = *reinterpret_cast<const u32*>(data + offset);
        u8 mode = (value >> 29) & 0x7;
        u32 numEntries = value & 0x1FFFFFFF;
        offset += sizeof(u32);

        u8 numBackgrounds;
        switch (mode) {
        case Types::Mode0: { numBackgrounds = 4; } break;
        case Types::Mode1: { numBackgrounds = 3; } break;
        case Types::Mode2: { numBackgrounds = 2; } break;
        default: { numBackgrounds = 0; } break;
        }

        for (u8 i = 0; i < numBackgrounds; ++i) {
            u32 tileMapId = *reinterpret_cast<const u32*>(data + offset);
            offset += sizeof(u32);

            if (tileMapId != (u32)-1) {
                ResourceLoader::load(Types::TileMap, tileMapId);
            }
        }

        PackedScene* result = new PackedScene();
        result->setMode((Types::EVideoMode)mode);

        return RefPointer<PackedScene>(result);
    }
}