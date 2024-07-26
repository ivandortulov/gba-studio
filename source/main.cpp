#include "test_bin.h"
#include "engine.hpp"
#include "gba_pack.hpp"
#include "reference.hpp"
#include "types.hpp"
#include "resource_loader.hpp"
#include "packed_scene.hpp"

using namespace GBS;

int main() {
	Engine engine(test_bin, test_bin_size);

	Node *scene = nullptr;
	RefPointer<Resource> tileMap0 = ResourceLoader::load(Types::TileMap, 0);
	RefPointer<Resource> tileMap1 = ResourceLoader::load(Types::TileMap, 1);

	// if (sceneData.isValid()) {
	// 	scene = sceneData->instance();
	// }

	// if (!scene) {
	// 	LOG_ERR("Failed to load main scene!");
	// 	return -1;
	// }

	// SceneTree::addCurrentScene(scene);

	return engine.run();
}