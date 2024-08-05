#include "resource_loader.hpp"
#include "../util/log.hpp"
#include "../core/macros.hpp"

namespace GBS {
    std::map<Types::EResourceType, ResourceLoader*> ResourceLoader::loaders;
    std::map<u32, RefPointer<Resource>> ResourceLoader::cache;

    ResourceLoader::~ResourceLoader() { }

    RefPointer<Resource> ResourceLoader::load(
        const u32 id
    ) {
        return ResourceLoader::load(RES_TYPE(id), RES_ID(id));
    }

    RefPointer<Resource> ResourceLoader::load(
        const Types::EResourceType type,
        const u32 id
    ) {
        if (loaders.find(type) == loaders.end()) {
            LOG_ERR("No loader registered for type %d", type);
            return RefPointer<Resource>();
        }

        if (cache.find(MAKE_RES_ID(type, id)) == cache.end()) {
            cache[MAKE_RES_ID(type, id)] = loaders[type]->loadInternal(id);
        }

        return cache[MAKE_RES_ID(type, id)];
    }

    void ResourceLoader::registerLoader(
        const Types::EResourceType type,
        ResourceLoader* loader
    ) {
        loaders[type] = loader;
    }
}