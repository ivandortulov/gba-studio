#include "scene_tree.hpp"

namespace GBS {
    SceneTree* SceneTree::instance = nullptr;

    void SceneTree::setCurrentScene(Node* scene) {
        currentScene = scene;
        root->addChild(currentScene);
        currentScene->propagateEnterTree();
        currentScene->propagateReady();
    }

    void SceneTree::iteration() {
        root->propagateIdleFrame();
    }
}