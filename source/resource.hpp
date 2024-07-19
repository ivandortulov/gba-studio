#pragma once

#include "reference.hpp"

namespace GBS {
    class Resource : public Reference {
        OBJECT(Resource, Reference)
    };
}