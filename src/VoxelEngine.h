#pragma once

#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Player;
class ShaderProgram;
class Scene;

class VoxelEngine {
public:
    VoxelEngine();
    ~VoxelEngine();

    void run();

    float deltaTime;
    float time;
    std::shared_ptr<Player> player;
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::shared_ptr<Scene> scene;

    GLFWwindow* window;

private:
    void initWindow();
    void initGL();
    void processInput();
    void update();
    void render();

    bool isRunning;
    double lastFrameTime;
};
