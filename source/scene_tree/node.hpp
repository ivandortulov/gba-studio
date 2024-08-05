#pragma once

#include "../core/reference.hpp"

namespace GBS {
    class Node : public Reference {
        OBJECT(Node, Reference)

        friend class SceneTree;

    public:
        enum {
            NOTIFICATION_ENTER_TREE,
		    NOTIFICATION_EXIT_TREE,
            NOTIFICATION_READY,
            NOTIFICATION_IDLE_FRAME,
        };

    public:
        Node() : parent(nullptr), isInsideTree(false) { }
        virtual ~Node() { }

    public:
        void addChild(Node* child);
        void removeChild(Node* child);

    public:
        virtual void ready() {};
        virtual void process(u32 delta) {};

    protected:
        void notification(u16 notification);

    private:
        void propagateEnterTree();
	    void propagateReady();
	    void propagateExitTree();
        void propagateIdleFrame();

    private:
        std::vector<Node*> children;
        Node* parent;
        bool isInsideTree;
    };
}