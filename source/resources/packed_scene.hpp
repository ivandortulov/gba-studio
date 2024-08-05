#pragma once

#include "../core/reference.hpp"
#include "../resources/resource.hpp"
#include "../scene_tree/node.hpp"
#include "../resources/tile_map.hpp"
#include "../core/types.hpp"

#include <vector>

namespace GBS {
    constexpr u32 INVALID_BG = (u32)-1;
    constexpr u16 INVALID_ID = (u16)-1;

    class PackedScene : public Resource {
        OBJECT(PackedScene, Resource);

        friend class ResourceLoaderScene;

        struct NodeData {
            u16 id;
            u16 type;
            u16 parent;
            std::string name;

            NodeData()
                : id(INVALID_ID)
                , type(Types::Node)
                , parent(INVALID_ID)
                , name("Node") {
            }
        };

    public:
        PackedScene();

    private:
        PackedScene(
            const Types::EVideoMode mode,
            const u32 backgrounds[Types::NumBackgrounds],
            const std::vector<NodeData>& nodes
        );

    public:
        Node* instantiate() const;

    public:
        inline void setMode(Types::EVideoMode mode) {
            this->mode = mode;
        }

        inline Types::EVideoMode getMode() const {
            return this->mode;
        }

    protected:
        Types::EVideoMode mode;
        u32 backgrounds[Types::NumBackgrounds];
        std::vector<NodeData> nodes;
    };
}