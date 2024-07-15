#pragma once

#include <gba_types.h>

#define ERR_GENERIC_FAILURE -1

namespace GBS {
    enum EVideoMode {
        Mode0,
        Mode1,
        Mode2,
        Mode3,
        Mode4
    };

    enum EBackground {
        Background0,
        Background1,
        Background2,
        Background3
    };

    enum EBackgroundSize {
        Size_256x256,
        Size_512x256,
        Size_256x512,
        Size_512x512
    };

    enum ESpriteSize {
        Square_8,
        Square_16,
        Square_32,
        Square_64,
        Rectangle_16x8,
        Rectangle_32x8,
        Rectangle_8x16,
        Rectangle_8x32,
        Rectangle_16x32,
        Rectangle_32x16,
        Rectangle_32x64,
        Rectangle_64x32
    };

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