#pragma once

namespace GBS {
    class ResourceManager;
    class Renderer;

    class SceneTree {
        public:
            SceneTree(
                const ResourceManager* resourceManager, 
                const Renderer* renderer);

        private:
            const ResourceManager* resourceManager;
            const Renderer* renderer;
    };
}