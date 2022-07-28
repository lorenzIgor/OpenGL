#pragma once
#include "Shader.h"
#include "Texture.h"

class Material
{
private:
    glm::vec4   m_color;
    Texture*    m_texture;
    Shader*     m_shader;
public:
    Material();
    ~Material();

    void Bind();
    void Unbind();
    
    inline Shader& getShader() const { return *m_shader; }
    
    inline glm::vec4 getColor() const { return m_color; }
    inline void getColor(glm::vec4& color) { m_color = color; }
        
};
