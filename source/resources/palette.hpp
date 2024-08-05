#pragma once

#include "resource.hpp"
#include <vector>

namespace GBS {
  class Palette : public Resource {
    OBJECT(Palette, Resource)

    friend class ResourceLoaderPalette;

  public:
    Palette() : numColors(0) { }

  private:
    Palette(
        bool background, 
        u8 numColors,
        const u8* ptr
    );

  public:
    inline void setNumColors(u8 numColors) {
      this->numColors = numColors;
    }

  private:
    u8 numColors;
  };
}