#pragma once

#include "reference.hpp"
#include "resource.hpp"

#include <map>
#include <string>

namespace GBS {
    class GBAPack;

    class ResourceManager {
        public:
            ResourceManager(const GBAPack* pack);
            ~ResourceManager();

        public:
            RefPointer<Resource> load(
                const std::string& path
            );

        private:
            const GBAPack* pack;

            std::map<u32, RefPointer<Resource>> resourceCache;
    };
}