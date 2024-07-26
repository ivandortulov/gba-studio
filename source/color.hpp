#pragma once

#include <gba_types.h>

namespace GBS {
    struct Color {
        union {
            struct {
                u8 r;
                u8 g;
                u8 b;
                u8 a;
            };

            u8 components[4];
        };
    };
}