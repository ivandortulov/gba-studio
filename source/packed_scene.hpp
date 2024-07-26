#pragma once

#include "reference.hpp"
#include "resource.hpp"
#include "node.hpp"
#include "types.hpp"

#include <vector>

namespace GBS {
    class PackedScene : public Resource {
        OBJECT(PackedScene, Resource);

    public:
        PackedScene();

    public:
        RefPointer<Node> instance() const;

    public:
        inline void setMode(Types::EVideoMode mode) {
            this->mode = mode;
        }

        inline Types::EVideoMode getMode() const {
            return this->mode;
        }

    protected:
        Types::EVideoMode mode;
        std::vector<RefPointer<Node>> nodes;
        RefPointer<Node> root;
    };
}