#include "packed_scene.hpp"

namespace GBS {
    PackedScene::PackedScene() : root(new Node()), mode(Types::Mode0) {
    }
}