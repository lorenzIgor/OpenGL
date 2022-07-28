#include "Material.h"

Material::Material()
{
    m_texture = new Texture("res/textures/sample.png");
    m_shader = new Shader("res/shaders/Basic.glsl");
}

Material::~Material()
{
    delete m_texture;
    delete m_shader;
}

void Material::Bind()
{
    m_shader->Bind();
    m_shader->SetUniforms4f("u_Color", getColor().x, getColor().y, getColor().z, getColor().w);
    
    if(m_texture)
    {
        m_shader->SetUniforms1i("u_Texture", 0);
        m_texture->Bind(0);
    }
}

void Material::Unbind()
{
    m_texture->Unbind();
    m_shader->Unbind();
}

