#pragma once

#include <gba_types.h>

#include "gba_pack.hpp"
#include "reference.hpp"
#include "renderer.hpp"
#include "scene_tree.hpp"
#include "resource_manager.hpp"

namespace GBS {
    class Engine {
        public:
            explicit Engine(const u8* pckPtr, const u32 pckSize);

            ~Engine();

        public:
            // void setCurrentScene(const RefPointer<Node>& scene);

            void tick();

        private:
            bool isInitialized;

            GBAPack* pack;

            SceneTree* sceneTree;
            ResourceManager* resourceManager;
            Renderer* renderer;
    };
}