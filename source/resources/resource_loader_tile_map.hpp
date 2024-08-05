#pragma once

#include "resource_loader.hpp"

namespace GBS {
    class ResourceLoaderTileMap : public ResourceLoader {
    public:
        virtual RefPointer<Resource> loadInternal(const u32 id) override;

    public:
        static ResourceLoader* getSingleton() {
            if (!instance) {
                instance = new ResourceLoaderTileMap();
            }

            return instance;
        }

    private:
        static ResourceLoaderTileMap* instance;
    };
}