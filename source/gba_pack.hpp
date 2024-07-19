#ifndef GBA_PACK_H_
#define GBA_PACK_H_

#include <gba_types.h>

#include <map>

#define MAGIC_GBRP "GBRP"

namespace GBS
{
	class GBAPack {
		enum EResourceType {
			Palette,
			TileSet,
			TileMap,
			Sprite,
			Script,
			Scene,
			Sound,

			NumResourceTypes
		};

		struct __attribute__((packed)) Header{
			char signature[4];
			u16 version;
			u32 indexOffset;
			u32 indexCount;
		};

		typedef struct {
			u32 id;
			u32 dataOffset;
			u32 dataSize;
		} __attribute__((packed)) IndexEntry;

		struct IndexTableEntry {
			EResourceType type;
			u32 id;
			const u8* data;
			u32 size;
		};

		struct __attribute__((packed)) PaletteHeader {
			u16 numColors;
		};

		struct __attribute__((packed)) TileSetHeader {
			u32 paletteId;
			u16 numTiles;
		};

		struct __attribute__((packed)) TileMapHeader {
			u32 tileSetId;
			u16 width;
			u16 height;
		};

		struct __attribute__((packed)) SpriteHeader {
			u8 size;
			u8 palette;
		};

	public:
		static GBAPack* getInstance();

		bool loadFromMemory(const u8* data, u32 size);
		void getResourceData(u32 resourceId, const u8*& data, u32& dataSize);

	public:
		void updateScrollAndLoadTiles(s16 newScrollX, s16 newScrollY);
		void loadTilesVertical(u16 startX, u16 startY, u16 endY, bool rightEdge);
		void loadTilesHorizontal(u16 startX, u16 endX, u16 startY, bool bottomEdge);

	private:
		GBAPack();

		static GBAPack* instance;

	private:
		std::map<u32, IndexTableEntry> indexTable;

		int loadedTilesStartX;
		int loadedTilesStartY;
		int loadedTilesWidth;
		int loadedTilesHeight;

	};
}

#endif