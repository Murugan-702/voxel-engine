#include "Player.h"
#include "VoxelEngine.h"
#include <GLFW/glfw3.h>
#include <iostream>

Player::Player(VoxelEngine* app, glm::vec3 position, float yaw, float pitch)
    : Camera(position, yaw, pitch), app(app) {
    glfwSetCursorPos(app->window, WIN_RES.x / 2.0, WIN_RES.y / 2.0);
    glfwSetInputMode(app->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Player::update() {
    keyboardControl();
    mouseControl();
    Camera::update();
}

// empty placeholder to match original
void Player::handleEvent() {
    // TO BE IMPLEMENTED SOON
}

void Player::keyboardControl() {
    float vel = PLAYER_SPEED * app->deltaTime;

    if (glfwGetKey(app->window, GLFW_KEY_W) == GLFW_PRESS) moveForward(vel);
    if (glfwGetKey(app->window, GLFW_KEY_S) == GLFW_PRESS) moveBack(vel);
    if (glfwGetKey(app->window, GLFW_KEY_A) == GLFW_PRESS) moveLeft(vel);
    if (glfwGetKey(app->window, GLFW_KEY_D) == GLFW_PRESS) moveRight(vel);
    if (glfwGetKey(app->window, GLFW_KEY_Q) == GLFW_PRESS) moveUp(vel);
    if (glfwGetKey(app->window, GLFW_KEY_E) == GLFW_PRESS) moveDown(vel);
}

void Player::mouseControl() {
    double xpos, ypos;
    glfwGetCursorPos(app->window, &xpos, &ypos);
    

    static double lastX = WIN_RES.x / 2.0;
    static double lastY = WIN_RES.y / 2.0;
    static bool firstMouse = true;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    double dx = xpos - lastX;
    double dy = lastY - ypos;  

    lastX = xpos;
    lastY = ypos;

    rotateYaw(static_cast<float>(dx * MOUSE_SENSITIVITY));
    rotatePitch(static_cast<float>(dy * MOUSE_SENSITIVITY));
}
