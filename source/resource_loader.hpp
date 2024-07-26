#pragma once

#include "types.hpp"
#include "reference.hpp"
#include "resource.hpp"

#include <map>

namespace GBS {
    class ResourceLoader {
    public:
        virtual ~ResourceLoader();

    public:
        static RefPointer<Resource> load(
            const Types::EResourceType type,
            const u32 id
        );

        static void registerLoader(
            const Types::EResourceType type,
            ResourceLoader* loader
        );

    protected:
        virtual RefPointer<Resource> loadInternal(const u32 id) = 0;

    private:
        static std::map<Types::EResourceType, ResourceLoader*> loaders;
        static std::map<u32, RefPointer<Resource>> cache;
    };
}
