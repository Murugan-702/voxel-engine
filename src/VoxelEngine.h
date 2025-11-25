#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Settings.h"

class VoxelEngine {
public:
    VoxelEngine();
    ~VoxelEngine();

    void run();

private:
    GLFWwindow* window;
    float deltaTime;
    float time;
    bool isRunning;

    void initWindow();
    void handleEvents();
    void update();
    void render();
};
