#pragma once

#include "resource_loader.hpp"

namespace GBS {
    class ResourceLoaderTileSet : public ResourceLoader {
    public:
        static ResourceLoader* getSingleton() {
            if (!instance) {
                instance = new ResourceLoaderTileSet();
            }
            return instance;
        }

    public:
        virtual RefPointer<Resource> loadInternal(u32 id) override;

    private:
        static ResourceLoaderTileSet* instance;
    };
}