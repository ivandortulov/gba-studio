#include "tile_map.hpp"

namespace GBS {
  TileMap::TileMap()
    : mapData(nullptr)
    , mapDataSize(0)
    , blockId(255) {

  }

  TileMap::TileMap(
    const u8* mapData,
    const u32 mapDataSize
  ) : mapData(mapData)
    , mapDataSize(mapDataSize)
    , blockId(255) {

  }
}