#include "node.hpp"
#include <algorithm>

namespace GBS {
    void Node::addChild(const RefPointer<Node>& child) {
        if (std::find(children.begin(), children.end(), child) != children.end()) {
            return;
        }

        children.push_back(child);
    }

    void Node::removeChild(const RefPointer<Node>& child) {
        auto it = std::remove(children.begin(), children.end(), child);
        if (it != children.end()) {
            children.erase(it, children.end());
        }
    }
}