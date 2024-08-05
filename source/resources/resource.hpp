#pragma once

#include "../core/reference.hpp"

namespace GBS {
    class Resource : public Reference {
        OBJECT(Resource, Reference)

    public:
        virtual bool isValid() const { return true; }
    };
}