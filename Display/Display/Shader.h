#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "includes/glad/glad.h"
#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/type_ptr.hpp"

#include <string.h>
#include <sstream>
#include <fstream>
#include <iostream>

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char*fragmentPath);

    void Use();

    void SetUniformBool(const std::string &name, bool value) const;

    void SetUniformInt(const std::string &name, int value) const;

    void SetUniformFloat(const std::string &name, float value) const;

    void SetUniformMat4(const std::string &name, glm::mat4 value) const;

private:
    unsigned int vertex_shader;
    unsigned int fragment_shader;

    enum ShaderType
    {
        VERTEX,
        FRAGMENT
    };

    void SetShaderFile(const char* filePath, ShaderType shaderType);

    void LinkAndDelet();
};

#endif // !SHADER_H

