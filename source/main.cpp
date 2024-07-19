#include "test_bin.h"
#include "engine.hpp"
#include "gba_pack.hpp"
#include "reference.hpp"

using namespace GBS;

int main() {
	Engine engine(test_bin, test_bin_size);

	// Node *scene = nullptr;
	// RefPointer<PackedScene> sceneData = ResourceLoader::load("res://main.scn");

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