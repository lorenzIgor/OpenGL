#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include "Renderer.h"

ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType 
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) 
    {
        if (line.find("#shader") != std::string::npos) {
            
            if(line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            } 
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else 
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };

}

Shader::Shader(const std::string& filepath) : m_RendererID(0), m_FilePath(filepath)
{
    const ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID))
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)malloc(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    const unsigned int program = glCreateProgram();
    const unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    const unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID))
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0))
}

void Shader::SetUniforms1i(const std::string& name, int v0)
{
    GLCall(glUniform1i(GetUniformLocation(name), v0))
}

void Shader::SetUniforms4f(const std::string& name, float v0, float v2, float v3, float v4)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v2, v3, v4))
}

void Shader::SetUniformsMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]))
}

int Shader::GetUniformLocation(const std::string& name) const
{
    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return  m_UniformLocationCache[name];

    int m_location = glGetUniformLocation(m_RendererID, name.c_str());
    m_UniformLocationCache[name] =  m_location;
    
    return m_location;
}
