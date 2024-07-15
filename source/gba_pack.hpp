#ifndef GBA_PACK_H_
#define GBA_PACK_H_

#include <gba_types.h>

#include <map>

#define MAGIC_GBRP "GBRP"

namespace GBS
{
	class GBAPack
	{
		typedef enum {
			BgPalette,
			TileSet,
			TileMap,
			SprPalette,
			Sprite,
			Script,
			Scene,
			Sound,

			NumResourceTypes
		} EResourceType;

		typedef struct {
			char signature[4];
			uint16_t version;
			uint32_t indexOffset;
			uint32_t indexCount;
		} __attribute__((packed)) FileHeader;

		typedef struct {
			uint16_t type;
			uint32_t dataOffset;
			uint32_t dataSize;
		} __attribute__((packed)) IndexEntry;

		struct IndexTableEntry {
			EResourceType type;
			u16 id;
			const u8* data;
			u32 size;
		};

		struct __attribute__((packed)) PaletteHeader {
			u16 numColors;
		};

		struct __attribute__((packed)) TileSetHeader {
			u16 colorMode;
			u16 numTiles;
			u16 palette;
		};

		struct __attribute__((packed)) TileMapHeader {
			u16 width;
			u16 height;
			u16 tileSet;
		};

		struct __attribute__((packed)) SpriteHeader {
			u8 size;
			u8 palette;
		};

	public:
		GBAPack();

	public:
		bool loadFromMemory(const u8* data, u32 size);
		void getResourceData(u16 resourceId, const u8*& data, u32& dataSize);

	public:
		void updateScrollAndLoadTiles(s16 newScrollX, s16 newScrollY);
		void loadTilesVertical(u16 startX, u16 startY, u16 endY, bool rightEdge);
		void loadTilesHorizontal(u16 startX, u16 endX, u16 startY, bool bottomEdge);

	private:
		std::map<u32, IndexTableEntry> indexTable;

		int loadedTilesStartX;
		int loadedTilesStartY;
		int loadedTilesWidth;
		int loadedTilesHeight;

	};
}

#endif