#pragma once
#include "Camera.h"
#include "Settings.h"
#include <glm/glm.hpp>

class VoxelEngine;

class Player : public Camera {
public:
    VoxelEngine* app;

    Player(VoxelEngine* app, glm::vec3 position = PLAYER_POS, float yaw = -90.0f, float pitch = 0.0f);

    void update();
    void handleEvent();      // keep as empty placeholder
    void keyboardControl();
    void mouseControl();
};
