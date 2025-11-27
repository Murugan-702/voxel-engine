#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    glm::mat4 m_proj;  // projection matrix
    glm::mat4 m_view;  // view matrix

    Camera(const glm::vec3& pos, float yaw, float pitch);

    void update();                 
    void updateViewMatrix();      
    void updateVectors();        

    void rotateYaw(float deltaX);
    void rotatePitch(float deltaY);

    void moveForward(float velocity);
    void moveBack(float velocity);
    void moveRight(float velocity);
    void moveLeft(float velocity);
    void moveUp(float velocity);
    void moveDown(float velocity);
};
