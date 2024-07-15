#pragma once

#include "reference.hpp"

namespace GBS {
    class Node : public Reference {
	public:
		void addChild(const RefPointer<Node>& child);
        void removeChild(const RefPointer<Node>& child);

        protected:
        std::vector<RefPointer<Node>> children;
	};
}