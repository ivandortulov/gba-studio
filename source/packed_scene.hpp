#pragma once

#include "resource.hpp"
#include "node.hpp"

namespace GBS {
    class PackedScene : public Resource {
        OBJECT(PackedScene, Resource)

        public:
            RefPointer<Node> instance() const;
    };
}