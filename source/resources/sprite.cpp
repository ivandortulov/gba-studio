#include "sprite.hpp"

namespace GBS {
    Sprite::Sprite(
        u16 numFrames, 
        Types::ESpriteSize size,
        const u8* data,
        const u32 dataSize,
        const RefPointer<Palette>& palette
    ) : numFrames(numFrames)
      , size(size)
      , palette(palette) {

    }
}