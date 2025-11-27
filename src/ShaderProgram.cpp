#include "ShaderProgram.h"
#include "Player.h"
#include "VoxelEngine.h"
#include <glm/glm.hpp>
#include <iostream>
ShaderProgram::ShaderProgram(VoxelEngine *app) : app(app)
{
    quad = getProgram("quad");
    setUniformsOnInit();
}

std::shared_ptr<Shader> ShaderProgram::getProgram(const std::string &shaderName)
{
    std::string vertPath = "shaders/" + shaderName + ".vert";
    std::string fragPath = "shaders/" + shaderName + ".frag";
    auto shader = std::make_shared<Shader>(vertPath, fragPath);
    return shader;
}

void ShaderProgram::setUniformsOnInit()
{
    quad->use();

    quad->setMat4("m_proj", app->player->m_proj);
    quad->setMat4("m_model", glm::mat4(1.0f));
}

void ShaderProgram::update()
{
    quad->use();

    quad->setMat4("m_view", app->player->m_view);
}
