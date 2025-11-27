#ifndef BASE_MESH_H
#define BASE_MESH_H

#include <vector>
#include <string>
#include <glad/glad.h>

class BaseMesh {
public:
    BaseMesh();
    virtual ~BaseMesh();

    void init();
    void render();
    
protected:
    virtual std::vector<float> getVertexData() = 0;     // must be implemented by derived mesh

protected:
    GLuint vao;
    GLuint vbo;
    GLuint program;   // shader program ID
    GLint vertexCount;
};

#endif
