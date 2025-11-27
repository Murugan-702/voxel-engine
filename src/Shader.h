#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

    unsigned int ID; 

private:
    std::string readFile(const std::string& filePath) const;
    void checkCompileErrors(unsigned int shader, const std::string& type) const;
};

#endif
