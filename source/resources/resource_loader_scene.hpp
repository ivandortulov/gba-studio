#pragma once

#include "resource_loader.hpp"

namespace GBS {
    class ResourceLoaderScene : public ResourceLoader {
    public:
        static ResourceLoader* getSingleton() {
            if (!instance) {
                instance = new ResourceLoaderScene();
            }
            return instance;
        }

    public:
        virtual RefPointer<Resource> loadInternal(u32 id) override;

    private:
        static ResourceLoaderScene* instance;
    };
}