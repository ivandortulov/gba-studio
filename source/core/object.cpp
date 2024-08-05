#include "object.hpp"

namespace GBS {
    void Object::initializeClass() {
        static bool isInitialized = false;
        if (isInitialized) {
            return;
        }
        // ClassDB::addClass<Object>();
        // bindMethods();
        isInitialized = true;
    }
}