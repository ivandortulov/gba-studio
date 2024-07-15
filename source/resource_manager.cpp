#include "resource_manager.hpp"

#include "gba_pack.hpp"


namespace GBS {
    ResourceManager::ResourceManager(const GBAPack* pack) : pack(pack) {

    }

    ResourceManager::~ResourceManager() {
        
    }
}