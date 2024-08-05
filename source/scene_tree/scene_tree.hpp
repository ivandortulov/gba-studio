#pragma once

#include "node.hpp"

namespace GBS {
    class SceneTree {

    public:
        static SceneTree* getInstance() {
            if (instance == nullptr) {
                instance = new SceneTree();
            }
            return instance;
        }

    public:
        void setCurrentScene(Node* scene);

        void iteration();

    private:
        SceneTree() 
            : root(new Node())
            , currentScene(nullptr) { 

        }

    private:
        static SceneTree* instance;

        Node* root;
        Node* currentScene;
    };
}