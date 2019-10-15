

#include "Shader.h"

Shader::Shader(const char * vertexPath, const char * fragmentPath)
{
    // creat shader program,get id
    // ensure the glad pointer has been set 
    ID = glCreateProgram();
    SetShaderFile(vertexPath,ShaderType::VERTEX);
    SetShaderFile(fragmentPath,ShaderType::FRAGMENT);
    LinkAndDelet();
}

#pragma region Public Fuctions

void Shader::Use()
{
    glUseProgram(ID);
}

void Shader::SetUniformBool(const std::string & name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetUniformInt(const std::string & name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetUniformFloat(const std::string & name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetUniformMat4(const std::string & name, glm::mat4 value) const
{
    // GL_FALSE ¾ØÕó ÊÇ·ñ×ªÖÃ
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

#pragma endregion

#pragma region Private Fuctions

void Shader::SetShaderFile(const char* filePath, ShaderType shaderType)
{
    std::string shaderCode;
    std::ifstream shaderFileStream;
    shaderFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        shaderFileStream.open(filePath, std::ios::in);
        std::stringstream shaderStringStream;
        shaderStringStream << shaderFileStream.rdbuf();
        shaderFileStream.close();
        shaderCode = shaderStringStream.str();
    }
    catch (const std::exception& ex)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULY_READ_!!! " << std::endl;
        std::cout << "Reason:" << ex.what() << std::endl;
    }

    const char* tempShaderCode = shaderCode.c_str();

    unsigned int  vfShader;
    int success;
    char infoLog[512];
    // vertex or fragment  shader  creat   compile  link
    switch (shaderType)
    {
        case Shader::VERTEX:
            vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            vfShader = vertex_shader;
            break;
        case Shader::FRAGMENT:
            fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            vfShader = fragment_shader;
            break;
        default:
            break;
    }

    glShaderSource(vfShader, 1, &tempShaderCode, nullptr);
    // compile and check
    glCompileShader(vfShader);    
    glGetShaderiv(vfShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vfShader, 512, NULL, infoLog);
        std::cout << "ERRO::SHADER::" + shaderType << " COMPILE_FAILED\n" << std::endl;
    }
    
    glAttachShader(ID, vfShader);
    

}

void Shader::LinkAndDelet()
{
    int success;
    char infoLog[512];

    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

#pragma endregion