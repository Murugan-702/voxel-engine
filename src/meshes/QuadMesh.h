#pragma once
#include <glad/glad.h>
#include <memory>

class VoxelEngine;

class QuadMesh {
public:
    QuadMesh(VoxelEngine* app);
    void render();

private:
    VoxelEngine* app; // store VoxelEngine pointer
    GLuint VAO, VBO;

    void initMesh();
};
