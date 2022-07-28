#include "Shape.h"

#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

Shape::Shape(const char* texture_path)
{
    this->setPosition({0.0f, 0.0f, 1.0f});
    this->setScale({1.0f, 1.0f, 1.0f});
    
    float arrPosModel_1[]{
        -1.0f, -1.0f, 0.0f, 0.0f, 
         1.0f, -1.0f, 1.0f, 0.0f, 
         1.0f,  1.0f, 1.0f, 1.0f, 
        -1.0f,  1.0f, 0.0f, 1.0f
    };

    unsigned int indices_model_1[] = {
        0, 1 ,2,
        2, 3 ,0
    };

    m_layout = new VertexBufferLayout();
    m_layout->Push<float>(2);
    m_layout->Push<float>(2);
    
    m_vertexBuffer = new VertexBuffer(arrPosModel_1, sizeof(arrPosModel_1));
    m_vertexArray = new VertexArray();    
    m_vertexArray->AddBuffer(m_vertexBuffer, m_layout);
    m_indexBuffer = new IndexBuffer(indices_model_1, sizeof(indices_model_1) / sizeof(unsigned int));

    m_shader = new Shader("res/shaders/Basic.glsl");
    m_shader->Bind();
    m_shader->SetUniforms4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    m_texture = new Texture(texture_path);
    m_texture->Bind(0);
    m_shader->SetUniforms1i("u_Texture", 0);
}

Shape::~Shape()
{
    delete m_layout;
    delete m_vertexArray;
    delete m_indexBuffer;
    delete m_vertexBuffer;
    delete m_texture;
    delete m_shader;
}

void Shape::onDraw(glm::mat4 proj, glm::mat4 view) const
{
    m_shader->Bind();
    m_texture->Bind(0);
    m_shader->SetUniformsMat4f("u_MVP", proj * view * this->getMatrix());
    m_vertexArray->Bind();
    m_indexBuffer->Bind();        
}
