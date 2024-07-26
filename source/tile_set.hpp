#pragma once

#include "reference.hpp"
#include "resource.hpp"
#include "palette.hpp"

namespace GBS {
    class Palette;

    class TileSet : public Resource {
        OBJECT(TileSet, Resource)

            friend class ResourceLoaderTileSet;

    public:
        TileSet();

    public:
        virtual bool isValid() const override {
            return blockId != 255;
        }

    private:
        RefPointer<Palette> palette;
        u8 blockId;
    };
}