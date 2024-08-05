#include "packed_scene.hpp"

#include "resource_loader.hpp"

#include <map>

namespace GBS {
    PackedScene::PackedScene() {
    }

    PackedScene::PackedScene(
        const Types::EVideoMode mode,
        const u32 backgrounds[Types::NumBackgrounds],
        const std::vector<NodeData>& nodes
    ) : mode(mode)
      , nodes(nodes) {
        for (u8 i = 0; i < Types::NumBackgrounds; ++i) {
            this->backgrounds[i] = backgrounds[i];
        }
    }

    Node* PackedScene::instantiate() const {
        if (mode > Types::Mode2) {
            // Framebuffer mode
        } else {
            // Tile mode
        }

        for (u8 i = 0; i < Types::NumBackgrounds; ++i) {
            if (backgrounds[i] != INVALID_BG) {
                RefPointer<TileMap> background = ResourceLoader::load(backgrounds[i]);
                if (background.isNull()) {
                    return nullptr;
                }
            }
        }

        std::map<u16, Node*> tree;
        Node* result = new Node();
        tree[(u16)-1] = result;

        for (NodeData nodeData : nodes) {
            Node* node = new Node();
            tree[nodeData.parent]->addChild(node);
            tree[nodeData.id] = node;
        }

        return result;
    }
}