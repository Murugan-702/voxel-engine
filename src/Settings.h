#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

// Resolution
static const glm::vec2 WIN_RES = glm::vec2(1600.0f, 900.0f);
static const glm::vec3 BG_COLOR = glm::vec3(0.1f, 0.16f, 0.25f);

// Camera
static const float ASPECT_RATIO = WIN_RES.x / WIN_RES.y;
static const float FOV_DEG = 50.0f;
static const float V_FOV = glm::radians(FOV_DEG);
static const float H_FOV = 2.0f * std::atan(std::tan(V_FOV * 0.5f) * ASPECT_RATIO);

static const float NEAR = 0.1f;
static const float FAR = 200000.0f;

static const float PITCH_MAX = glm::radians(89.0f);

// Player
static const float PLAYER_SPEED = 0.5f;
static const float PLAYER_ROT_SPEED = 0.003f;
static const glm::vec3 PLAYER_POS = glm::vec3(0.0f, 0.0f, 1.0f);
static const float MOUSE_SENSITIVITY = 0.002f;
