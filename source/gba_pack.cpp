#include "gba_pack.hpp"

#include <iostream>
#include <memory.h>
#include "log.hpp"

#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <gba_dma.h>
#include <gba_sprites.h>

#include <vector>
#include <string>

#define GBRP_MAGIC 0x50524247

namespace GBS {
    const u8 TILE_SIZE = 8;
    const u16 TYPE_MASK = 0xE000;
    const u16 COUNT_MASK = 0x1FFF;

    static const char* const RES_TYPES[] = {
        "BgPalette",
		"TileSet",
		"TileMap",
		"SprPalette",
		"Sprite",
		"Script",
		"Scene",
		"Sound"
    };

    GBAPack::GBAPack()
    {
        loadedTilesStartX = 0;
        loadedTilesStartY = 0;
        loadedTilesWidth = 30;
        loadedTilesHeight = 20;
    }

    bool GBAPack::loadFromMemory(const u8* data, u32 size) {
        LOG_DEBUG("Loading GameBoy Advance Pack from memory ...");

        if (size < sizeof(FileHeader)) {
            LOG_ERR("Not a valid GameBoy Advance Pack!");
            return false;
        }

        FileHeader header;
        memcpy(&header, data, sizeof(FileHeader));

        if (*reinterpret_cast<u32*>(header.signature) != GBRP_MAGIC) {
            LOG_ERR("Invalid signature in the GameBoy Advance Pack!");
            return false;
        }

        // Ensure the index offset and size are within the bounds of the file
        if (header.indexOffset + header.indexCount * sizeof(IndexEntry) > size) {
            LOG_ERR("Index table extends beyond file size!");
            return false;
        }

        // Move the pointer to the start of the index table
        const u8* indexPtr =
            data + header.indexOffset;
        const u32 dataStartOffset =
            header.indexOffset + header.indexCount * sizeof(IndexEntry);

        IndexEntry entry;

        LOG_DEBUG("Index table:");
        for (u32 i = 0; i < header.indexCount; ++i) {
            memcpy(&entry, indexPtr, sizeof(IndexEntry));
            indexPtr += sizeof(IndexEntry);

            u8 type = (entry.type & TYPE_MASK) >> 13;
            u16 id = entry.type & COUNT_MASK;

            LOG_DEBUG("  %d. id=%d, type=%s, offset=%lu, size=%lu", 
                i + 1,
                id,
                RES_TYPES[type], 
                entry.dataOffset, 
                entry.dataSize
            );

            indexTable[entry.type] = {
                (EResourceType)type,
                id,
                data + dataStartOffset + entry.dataOffset,
                entry.dataSize
            };
        }

        // ------------- This is just for testing ------------

        const u8* ptr;
        u32 dataSize;

        // ----- BG Palette ----
        u16 id = (BgPalette << 13) & 0xFFFF;
        getResourceData(id, ptr, dataSize);
        DMA3COPY(
            ptr,
            BG_PALETTE,
            dataSize / 2
        );

        // ----- Spr Palette ----
        id = (SprPalette << 13) & 0xFFFF;
        getResourceData(id, ptr, dataSize);
        DMA3COPY(
            ptr,
            SPRITE_PALETTE,
            dataSize / 2
        );

        // ----- Tile Set ----
        id = (TileSet << 13) & 0xFFFF;
        getResourceData(id, ptr, dataSize);
        DMA3COPY(
            ptr,
            TILE_BASE_ADR(0),
            dataSize / 2
        );

        REG_BG0CNT = BG_256_COLOR | BG_SIZE_0 | BG_TILE_BASE(0) | BG_MAP_BASE(31);
        REG_BG0HOFS = 0;
        REG_BG0VOFS = 0;

        // // ----- Tile Map ----
        id = (TileMap << 13) & 0xFFFF;
        getResourceData(id, ptr, dataSize);
        DMA3COPY(
            ptr,
            MAP_BASE_ADR(31),
            dataSize
        );

        // // ----- Sprites ----
        id = (Sprite << 13) & 0xFFFF;
        getResourceData(id, ptr, dataSize);
        DMA3COPY(
            ptr,
            SPRITE_GFX,
            dataSize / 2
        );

        // Configure position and properties in OAM
        OBJATTR* sprite = &OAM[0];
        sprite->attr0 = ATTR0_COLOR_256 | ATTR0_SQUARE | ATTR0_TYPE_NORMAL | ATTR0_NORMAL | OBJ_Y(50);
        sprite->attr1 = OBJ_SIZE(1) | OBJ_X(100); // 16x16 pixels
        sprite->attr2 = OBJ_CHAR(0) | ATTR2_PRIORITY(0) | ATTR2_PALETTE(0); // Tile index and palette bank

        id = ((Sprite << 13) | 1) & 0xFFFF;
        getResourceData(id, ptr, dataSize);
        DMA3COPY(
            ptr,
            SPRITE_GFX + 128,
            dataSize / 2
        );

        id = ((Sprite << 13) | 2) & 0xFFFF;
        getResourceData(id, ptr, dataSize);
        DMA3COPY(
            ptr,
            SPRITE_GFX + 256,
            dataSize / 2
        );

        id = ((Sprite << 13) | 3) & 0xFFFF;
        getResourceData(id, ptr, dataSize);
        DMA3COPY(
            ptr,
            SPRITE_GFX + 256 + 128,
            dataSize / 2
        );

        return true;
    }

    void GBAPack::getResourceData(u16 resourceId, const u8*& data, u32& dataSize)
    {
        if (indexTable.find(resourceId) == indexTable.end()) {
            data = NULL;
            dataSize = 0;
        }

        u8 type = (indexTable[resourceId].type & TYPE_MASK) >> 13;
        u16 id = indexTable[resourceId].type & COUNT_MASK;

        data = indexTable[resourceId].data;
        dataSize = indexTable[resourceId].size;

        u32 size = 0;
        switch(type) {
            case BgPalette: { size = sizeof(PaletteHeader);  } break;
            case TileSet: { size = sizeof(TileSetHeader); } break;
			case TileMap: { size = sizeof(TileMapHeader); } break;
            case SprPalette: { size = sizeof(PaletteHeader); } break;
			case Sprite: { size = sizeof(SpriteHeader); } break;
        }

        data += size;
        dataSize -= size;
    }

    void GBAPack::updateScrollAndLoadTiles(s16 newScrollX, s16 newScrollY)
    {
        const u16 mapWidth = 32;
        const u16 mapHeight = 32;

        // Calculate the maximum allowed scroll values
        s16 maxScrollX = (mapWidth - loadedTilesWidth) * TILE_SIZE;  // mapWidth should be 32 and TILE_SIZE should be 8
        s16 maxScrollY = (mapHeight - loadedTilesHeight) * TILE_SIZE; // mapHeight should also be 32

        // Clamp new scroll values to prevent scrolling beyond the map edges
        newScrollX = std::min(maxScrollX, std::max((s16)0, newScrollX));
        newScrollY = std::min(maxScrollY, std::max((s16)0, newScrollY));

        // Convert pixel scroll to tile indices
        s16 newStartTileX = newScrollX / TILE_SIZE;
        s16 newStartTileY = newScrollY / TILE_SIZE;

        // Calculate changes in scroll position in terms of tiles
        int deltaX = newStartTileX - loadedTilesStartX;
        int deltaY = newStartTileY - loadedTilesStartY;

        if (deltaX != 0 || deltaY != 0)
        {
            // Update the portion of the map that is loaded based on scroll direction
            if (deltaX > 0)
            {
                // Scroll right, load new column(s) on the right edge
                loadTilesVertical(newStartTileX + loadedTilesWidth - 1, deltaY, deltaY + loadedTilesHeight - 1, true);
            }
            else if (deltaX < 0)
            {
                // Scroll left, load new column(s) on the left edge
                loadTilesVertical(newStartTileX, deltaY, deltaY + loadedTilesHeight - 1, false);
            }

            if (deltaY > 0)
            {
                // Scroll down, load new row(s) at the bottom
                loadTilesHorizontal(deltaX, deltaX + loadedTilesWidth - 1, newStartTileY + loadedTilesHeight - 1, true);
            }
            else if (deltaY < 0)
            {
                // Scroll up, load new row(s) at the top
                loadTilesHorizontal(deltaX, deltaX + loadedTilesWidth - 1, newStartTileY, false);
            }

            // Update loaded tiles tracking
            loadedTilesStartX = newStartTileX;
            loadedTilesStartY = newStartTileY;
        }

        BG_OFFSET[0].x = newScrollX;
        BG_OFFSET[0].y = newScrollY;
    }

    void GBAPack::loadTilesVertical(u16 startX, u16 startY, u16 endY, bool rightEdge)
    {
        u16 vramOffset = rightEdge ? (loadedTilesWidth - 1) : 0;
        u32 tileIndex;
        u16* tileDataPtr;

        for (u16 y = startY; y <= endY; y++)
        {
            tileIndex = y * 32 + startX; // Calculate index in the full tile map
            tileDataPtr = (u16*)(indexTable[TileMap].data + tileIndex * TILE_SIZE); // Pointer to the tile data

            // Calculate the VRAM address to load the tile into
            u16* vramAddress = ((u16*)TILE_BASE_ADR(0) + (y * 32 + vramOffset) * TILE_SIZE);

            // Copy the tile data into VRAM
            DMA3COPY(tileDataPtr, vramAddress, TILE_SIZE / 2);
        }
    }

    void GBAPack::loadTilesHorizontal(u16 startX, u16 endX, u16 startY, bool bottomEdge)
    {
        // Determine the VRAM offset for horizontal tile loading
        u16 vramOffset = bottomEdge ? (loadedTilesHeight - 1) : 0;
        u32 tileIndex;
        u16* tileDataPtr;

        for (u16 x = startX; x <= endX; x++) {
            tileIndex = startY * 32 + x; // Calculate index in the full tile map
            tileDataPtr = (u16*)(indexTable[TileMap].data + tileIndex * TILE_SIZE); // Pointer to the tile data

            // Calculate the VRAM address to load the tile into
            u16* vramAddress = ((u16*)TILE_BASE_ADR(0) + (vramOffset * 32 + x) * TILE_SIZE);

            // Copy the tile data into VRAM
            DMA3COPY(tileDataPtr, vramAddress, TILE_SIZE / 2);
        }
    }

}