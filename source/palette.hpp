#pragma once

#include "resource.hpp"
#include <vector>

namespace GBS {
  class Palette : public Resource {
    OBJECT(Palette, Resource)

  public:
    Palette() : numColors(0) { }

  public:
    inline void setNumColors(u8 numColors) {
      this->numColors = numColors;
    }

  private:
    u8 numColors;
  };
}