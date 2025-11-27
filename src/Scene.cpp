#include "Scene.h"
#include <iostream>

Scene::Scene(VoxelEngine* app) : app(app) {
    quad = std::make_unique<QuadMesh>(app);
}

void Scene::update() {
    // TO BE IMPLEMENTED SOON
}

void Scene::render() {

    quad->render();
}
