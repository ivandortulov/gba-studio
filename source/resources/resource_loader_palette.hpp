#pragma once

#include "resource_loader.hpp"

namespace GBS {
    class ResourceLoaderPalette : public ResourceLoader {
    public:
        virtual RefPointer<Resource> loadInternal(const u32 id) override;

    public:
        static ResourceLoader* getSingleton() {
            if (!instance) {
                instance = new ResourceLoaderPalette();
            }

            return instance;
        }

    private:
        static ResourceLoaderPalette* instance;
    };
}