#include "palette.hpp"
#include "../graphics/renderer.hpp"

namespace GBS {
    Palette::Palette(
        bool background, 
        u8 numColors,
        const u8* ptr
    ) { 
        Renderer::getInstance()->loadPalette(
            ptr, numColors * sizeof(u16), background
        );
    }
}