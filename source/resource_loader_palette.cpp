#include "resource_loader_palette.hpp"

#include "macros.hpp"
#include "gba_pack.hpp"
#include "palette.hpp"
#include "log.hpp"
#include "renderer.hpp"

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
            LOG_ERR("Failed to load palette resource with id %d", id);
            return RefPointer<Palette>();
        }

        u32 offset = 0;
        u8 background = *data;
        offset += sizeof(u8);
        u8 numColors = *(data + offset);
        offset += sizeof(u8);

        Palette* result = new Palette();
        result->setNumColors(numColors);

        Renderer::getInstance()->loadPalette(
            data + offset, dataSize - offset, background
        );

        return RefPointer<Palette>(result);
    }
}