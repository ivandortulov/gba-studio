#pragma once

#include <gba_types.h>

namespace GBS {
    class Engine {
        public:
            explicit Engine(const u8* pckPtr, const u32 pckSize);

            ~Engine();

        public:
            int run();

        private:
            bool isInitialized;
    };
}