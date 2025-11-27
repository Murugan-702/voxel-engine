#ifndef SCENE_H
#define SCENE_H

#include "meshes/QuadMesh.h"
#include <memory>

class VoxelEngine;  // forward declare (app)

class Scene {
public:
    Scene(VoxelEngine* app);
    ~Scene() = default;

    void update();
    void render();

private:
    VoxelEngine* app;
    std::unique_ptr<QuadMesh> quad;
};

#endif
