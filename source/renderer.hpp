#pragma once

#include <gba_types.h>

#include "types.hpp"

#define ERR_GENERIC_FAILURE -1

namespace GBS {
    class Renderer {
    public:
        struct VideoConfig {
            EVideoMode videoMode;
            bool bgEnabled[4];
            EBackgroundSize bgSize[4];
            bool bgFullColor[4];
        };

    public:
        void setVideoMode(const VideoConfig& config);

    private:
        bool isInitialized;
    };
}