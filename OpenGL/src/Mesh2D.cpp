#include "Mesh2D.h"

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

Mesh2D::Mesh2D()
{
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
}

Mesh2D::~Mesh2D()
{
    delete m_vertexArray;
    delete m_indexBuffer;
    delete m_vertexBuffer;
    delete m_layout;
}

void Mesh2D::Bind()
{
    m_vertexArray->Bind();
    m_indexBuffer->Bind();
}

void Mesh2D::Unbind()
{
    m_vertexArray->Unbind();
    m_indexBuffer->Unbind();

}
