#pragma once

namespace GBS {
    class GBAPack;

    class ResourceManager {
        public:
            ResourceManager(const GBAPack* pack);
            ~ResourceManager();

        private:
            const GBAPack* pack;
    };
}