#pragma once

#include "resource.hpp"
#include "tile_set.hpp"

namespace GBS {
  class TileMap : public Resource {
    OBJECT(TileMap, Resource)

      friend class ResourceLoaderTileMap;

  public:
    TileMap();

  private:
    explicit TileMap(
      const u8* mapData,
      const u32 mapDataSize
    );

  private:
    const u8* mapData;
    u32 mapDataSize;
    u8 blockId;
    RefPointer<TileSet> tileSet;
  };
}