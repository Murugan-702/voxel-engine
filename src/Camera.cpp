#include "Camera.h"
#include "Settings.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Camera::Camera(const glm::vec3& pos, float yawDeg, float pitchDeg)
    : position(pos)
{
    // Store angles in radians
    yaw   = glm::radians(yawDeg);
    pitch = glm::radians(pitchDeg);

    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // Initialize vectors
    forward = glm::vec3(0.0f, 0.0f, -1.0f);
    right   = glm::vec3(1.0f, 0.0f, 0.0f);
    up      = glm::vec3(0.0f, 1.0f, 0.0f);

    m_proj = glm::perspective(V_FOV, ASPECT_RATIO, NEAR, FAR);
    m_view = glm::mat4(1.0f);

    update(); // Initialize vectors properly
}

void Camera::update() {
    updateVectors();
    updateViewMatrix();
}

void Camera::updateViewMatrix() {
    m_view = glm::lookAt(position, position + forward, up);
}

void Camera::updateVectors() {
    // Compute forward from yaw and pitch (camera relative)
    forward.x = cos(yaw) * cos(pitch);
    forward.y = sin(pitch);
    forward.z = sin(yaw) * cos(pitch);
    forward = glm::normalize(forward);

    // Recalculate right and up vectors relative to camera
    right = glm::normalize(glm::cross(forward,worldUp));
    up    = glm::normalize(glm::cross(forward,right));
}

void Camera::rotateYaw(float dx) {
    yaw += dx;   
    updateVectors(); // immediately update vectors
}

void Camera::rotatePitch(float dy) {
    pitch -= dy;  // invert like Python
    pitch = glm::clamp(pitch, -PITCH_MAX, PITCH_MAX);
    updateVectors();
}

// Camera-relative movement (works like Pygame)
void Camera::moveForward(float velocity) { position += forward * velocity; }
void Camera::moveBack(float velocity)    { position -= forward * velocity; }
void Camera::moveRight(float velocity)   { position += right * velocity; }
void Camera::moveLeft(float velocity)    { position -= right * velocity; }
void Camera::moveUp(float velocity)      { position -= up * velocity; }   // use worldUp
void Camera::moveDown(float velocity)    { position += up * velocity; }   // use worldUp
