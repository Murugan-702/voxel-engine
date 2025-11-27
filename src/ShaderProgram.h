#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <memory>
#include "Shader.h"


class VoxelEngine;

class ShaderProgram {
public:
    ShaderProgram(VoxelEngine* app); 

    void update();
    std::shared_ptr<Shader> quad;

    std::shared_ptr<Shader> getProgram(const std::string& shaderName);
    void setUniformsOnInit();

    VoxelEngine* app; // works now
};

#endif
