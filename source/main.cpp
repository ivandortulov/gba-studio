#include "test_bin.h"
#include "gbs.hpp"

using namespace GBS;

int main() {
	Engine engine(test_bin, test_bin_size);
	RefPointer<PackedScene> sceneData = ResourceLoader::load(Types::Scene, 0);
	Node* scene = sceneData->instantiate();
	SceneTree::getInstance()->setCurrentScene(scene);
	return engine.run();
}