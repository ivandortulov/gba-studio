
// #include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
// #include <gba_input.h>
// #include <gba_dma.h>
// #include <gba_sprites.h>

// #include "test_bin.h"

#include "gba_pack.hpp"
//#include "display_core.hpp"

#include "reference.hpp"

#include "engine.hpp"
#include "node.hpp"
#include "log.hpp"

#include "test_bin.h"

namespace GBS {
	struct Resource : public Reference {
		u16 id;

		virtual ~Resource() {}
	};

	struct Texture : public Resource {};

	class Sprite : public Node {
	public:
		void setTexture(const RefPointer<Texture>& texture)
		{

		}
	};

	RefPointer<Resource> load(const char* path) {
		// Dummy implementation for illustration
		return new Texture();
	}
}

#define ROM_START 0x08000000
#define ROM_END   0x09FFFFFF

#define MAGIC_BYTES 0x47425250

const u8* findMagicBytes() {
    const u8* addr = (u8*)ROM_START;
    while ((uint32_t)addr < ROM_END - 4) {
        if (addr[0] == 'G' && addr[1] == 'B' && addr[2] == 'R' && addr[3] == 'P') {
            return addr;
        }
        addr++;
    }
    return NULL;
}

int main() {
	irqInit();
	irqEnable(IRQ_VBLANK);

	GBS::Logger::log(GBS::LOG_DEBUG, "%p - %p", test_bin, findMagicBytes());

	SetMode(MODE_0 | BG0_ENABLE | OBJ_ENABLE | OBJ_1D_MAP);

	GBS::Engine engine(test_bin, test_bin_size);

	// GBS::DisplayCore displayCore;
	// displayCore.set_video_mode(MODE_0);

	// BG_PALETTE[0] = RGB5(31, 0, 0); // Red

	// auto sprite = new GBS::Sprite();
	// GBS::RefPointer<GBS::Texture> texture = GBS::load("res://textures/hello_world.png");
	// sprite->setTexture(texture);

	// auto root = new GBS::Node();
	// root->addChild(sprite);

	// engine.setCurrentScene(root);

	while (1) {
		VBlankIntrWait();

		engine.tick();
	}

	return 0;
}

// irqInit();
// irqEnable(IRQ_VBLANK);

// // Allow Interrupts
// REG_IME = 1;

// GBS::GBAPack pack;
// pack.loadFromMemory(test_bin, test_bin_size);

// core.load_palette(bg_palette_bin, true, bg_palette_bin_size / 2);
// DMA3COPY(bg_palette_bin, BG_PALETTE, DMA_ENABLE | DMA16 | (bg_palette_bin_size / 2));
// BG_PALETTE[0] = RGB5(31, 0, 0); // Red
// BG_PALETTE[1] = RGB5(0, 31, 0); // Green
// BG_PALETTE[2] = RGB5(0, 0, 31); // Blue
// BG_PALETTE[3] = RGB5(31, 31, 0); // Yellow

// Turn on Mode 0 with all backgrounds active
// GBS::DisplayCore core;
// core.set_video_mode(MODE_0);

// u16 scrollx = 0;
// u8 scrolldelay = 0;
// u8 frameDelay = 0;
// u8 frame = 0;

// OBJATTR* sprite = &OAM[0];
// sprite->attr0 = ATTR0_COLOR_256 | ATTR0_SQUARE | ATTR0_NORMAL | OBJ_Y(50);
// sprite->attr1 = OBJ_SIZE(1) | OBJ_X(100); // 16x16 pixels

		// if (frameDelay == 6)
	// {
	// 	frameDelay = 0;
	// 	sprite->attr2 = 8 * frame | ATTR2_PRIORITY(0) | ATTR2_PALETTE(0); // Tile index and palette bank
	// 	frame = (frame + 1) % 4;
	// }
	// else
	// {
	// 	frameDelay ++;
	// }

	// if (scrolldelay == 2) 
	// {
	// 	scrolldelay = 0;

	// 	if (scrollx != 32 * 8)
	// 	{
	// 		scrollx++;
	// 		pack.updateScrollAndLoadTiles(scrollx, scrollx);
	// 	}
	// }
	// else 
	// {
	// 	scrolldelay++;
	// }