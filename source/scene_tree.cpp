#include "scene_tree.hpp"

#include "resource_manager.hpp"
#include "renderer.hpp"


namespace GBS {
    SceneTree::SceneTree(
        const ResourceManager* resourceManager,
        const Renderer* Renderer
    ) : resourceManager(resourceManager)
        , renderer(renderer) {

    }
}