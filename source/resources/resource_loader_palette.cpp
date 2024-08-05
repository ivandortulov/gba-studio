#include "resource_loader_palette.hpp"

#include "../core/macros.hpp"
#include "gba_pack.hpp"
#include "palette.hpp"
#include "../util/log.hpp"
#include "../graphics/renderer.hpp"
#include "../util/stream_reader.hpp"

namespace GBS {
    ResourceLoaderPalette* ResourceLoaderPalette::instance = nullptr;

    RefPointer<Resource> ResourceLoaderPalette::loadInternal(u32 id) {
        const u8* data;
        u32 dataSize;

        GBAPack::getInstance()->getResourceData(
            MAKE_RES_ID(Types::Palette, id),
            data,
            dataSize
        );

        if (data == nullptr) {
            LOG_ERR("Failed to load palette resource with id %u", id);
            return RefPointer<Palette>();
        }

        u8 background;
        u8 numColors;

        StreamReader reader(data, dataSize);
        reader.read(background);
        reader.read(numColors);

        ASSERT_EQ(numColors * 2, reader.getRemaining(), "Malformed palette");
        if (numColors * sizeof(u16) != reader.getRemaining()) {
            LOG_ERR("Invalid palette with id %u", id);
            return RefPointer<Palette>();
        }

        Palette* result = new Palette(
            background, 
            numColors,
            data + reader.getPosition()
        );

        return RefPointer<Palette>(result);
    }
}