#include "QuadMesh.h"
#include "../VoxelEngine.h"
#include "../ShaderProgram.h"
#include <iostream>

QuadMesh::QuadMesh(VoxelEngine* app) : app(app) {
    initMesh();
}

void QuadMesh::initMesh() {
  
    float vertices[] = {
        // positions        // colors
         0.5f,  0.5f, 0.0f, 0.f, 1.f, 0.f,  // green
        -0.5f,  0.5f, 0.0f, 1.f, 0.f, 0.f,  // red
        -0.5f, -0.5f, 0.0f, 1.f, 1.f, 0.f,  // yellow
         0.5f,  0.5f, 0.0f, 0.f, 1.f, 0.f,  // green
        -0.5f, -0.5f, 0.0f, 1.f, 1.f, 0.f,  // yellow
         0.5f, -0.5f, 0.0f, 0.f, 0.f, 1.f   // blue
    };



    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Check attribute bindings
    GLint loc0, loc1;
    glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &loc0);
    glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &loc1);
  

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void QuadMesh::render() {
    // Activate shader
    app->shaderProgram->quad->use();
    GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);


    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
