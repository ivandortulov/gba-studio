#include "resource_loader_scene.hpp"
#include "gba_pack.hpp"
#include "../core/types.hpp"
#include "../util/log.hpp"
#include "../core/macros.hpp"
#include "packed_scene.hpp"
#include "tile_map.hpp"
#include "../util/stream_reader.hpp"

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

        StreamReader reader(data, dataSize);

        u32 modeAndNumEntities;
        reader.read(modeAndNumEntities);
        u8 mode = (modeAndNumEntities >> 29) & 0x7;
        u32 numEntries = modeAndNumEntities & 0x1FFFFFFF;

        u8 numBackgrounds;
        switch (mode) {
        case Types::Mode0: { numBackgrounds = 4; } break;
        case Types::Mode1: { numBackgrounds = 3; } break;
        case Types::Mode2: { numBackgrounds = 2; } break;
        default: { numBackgrounds = 0; } break;
        }

        u32 backgrounds[Types::NumBackgrounds] = {
            (u32)INVALID_RES, 
            (u32)INVALID_RES, 
            (u32)INVALID_RES, 
            (u32)INVALID_RES
        };

        for (u8 i = 0; i < numBackgrounds; ++i) {
            u32 tileMapId;
            reader.read(tileMapId);

            if (tileMapId != INVALID_RES) {
                backgrounds[i] = tileMapId;
            }
        }

        std::vector<PackedScene::NodeData> nodes;
        for (u32 i = 0; i < numEntries; ++i) {
            u8 entryType;
            reader.read(entryType);

            if (entryType == Types::Node) {
                PackedScene::NodeData node;

                u16 numProperties;
                reader.read(numProperties);

                for (u16 i = 0; i < numProperties; ++i) {
                    u16 propType;
                    reader.read(propType);

                    switch (propType)
                    {
                    case Types::Id: {
                        reader.read(node.id);
                    }
                    break;

                    case Types::Parent: {
                      reader.read(node.parent);
                    }
                    break;

                    case Types::Type: {
                      reader.read(node.type);
                    }
                    break;

                    case Types::Name: {
                        node.name = reader.readStr();
                    }
                    break;

                    default:
                        break;
                    }
                }

                nodes.push_back(node);
            }
        }

        PackedScene* result = new PackedScene(
            (Types::EVideoMode)mode,
            backgrounds,
            nodes
        );

        return RefPointer<PackedScene>(result);
    }
}