#include "../core/types.hpp"
#include "palette.hpp"
#include "resource.hpp"


namespace GBS {
    class Sprite : public Resource {
        OBJECT(Sprite, Resource)

        friend class ResourceLoaderSprite;

        public:
        
        private:
            Sprite(
                u16 numFrames, 
                Types::ESpriteSize size,
                const u8* data,
                const u32 dataSize,
                const RefPointer<Palette>& palette
            );

        private:
            u16 numFrames;
            Types::ESpriteSize size;
            RefPointer<Palette> palette;
    };
}