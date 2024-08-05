#include "node.hpp"
#include <algorithm>

namespace GBS {
    void Node::addChild(Node* child) {
        if (child == nullptr) {
            LOG_WARN("Tried to add a null child");
            return;
        }

        if (child == this) {
            LOG_WARN("Tried to add node as a child of itself");
            return;
        }

        if (child->parent != nullptr) {
            LOG_ERR("Node already has a parent");
            return;
        }

        if (std::find(children.begin(), children.end(), child) != children.end()) {
            LOG_WARN("Node already a child of parent");
            return;
        }

        children.push_back(child);
        child->parent = this;
    }

    void Node::removeChild(Node* child) {
        if (!child) {
            return;
        }

        auto it = std::remove(children.begin(), children.end(), child);
        if (it == children.end()) {
            return;
        }

        children.erase(it, children.end());
        (*it)->parent = nullptr;
    }

    void Node::notification(u16 notification) {
        switch(notification) {
            case NOTIFICATION_READY: {
                ready();
            }
            break;

            case NOTIFICATION_IDLE_FRAME: {
                process(0);
            }
            break;
        }
    }

    void Node::propagateEnterTree() {
        if (parent) {
            // TODO: Set tree
        }

        isInsideTree = true;

        notification(NOTIFICATION_ENTER_TREE);

        for (auto child : children) {
            if (!child->isInsideTree) {
                child->propagateEnterTree();
            }
        }
    }

    void Node::propagateReady() {
        for (auto child : children) {
            child->propagateReady();
        }

        notification(NOTIFICATION_READY);
    }

    void Node::propagateIdleFrame() {
        notification(NOTIFICATION_IDLE_FRAME);

        for (auto child : children) {
            child->propagateIdleFrame();
        }
    }
}