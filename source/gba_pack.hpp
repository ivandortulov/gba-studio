#ifndef GBA_PACK_H_
#define GBA_PACK_H_

#include <gba_types.h>

#include <map>

#include "macros.hpp"

#define MAGIC_GBRP "GBRP"

namespace GBS
{
	class GBAPack {

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

		struct PACKED Header {
			char signature[4];
			u16 version;
			u32 indexOffset;
			u32 indexCount;
		};

		typedef struct {
			u32 id;
			u32 dataOffset;
			u32 dataSize;
		} PACKED IndexEntry;

		struct IndexTableEntry {
			const u8* data;
			u32 size;
		};

		struct PACKED PaletteHeader {
			u8 background;
			u8 numColors;
		};

		struct PACKED TileSetHeader {
			u32 paletteId;
			u16 numTiles;
		};

		struct PACKED TileMapHeader {
			u32 tileSetId;
			u16 width;
			u16 height;
		};

		struct PACKED SpriteHeader {
			u8 size;
			u8 palette;
		};

#ifdef _MSC_VER
#pragma pack(pop)
#endif

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
		const u8* dataStart;
		std::map<u32, IndexTableEntry> indexTable;

		int loadedTilesStartX;
		int loadedTilesStartY;
		int loadedTilesWidth;
		int loadedTilesHeight;

	};
}

#endif