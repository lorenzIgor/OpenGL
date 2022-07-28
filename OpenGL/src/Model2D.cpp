#include "Model2D.h"

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

Model2D::Model2D()
{
    m_mesh = new Mesh2D();
    m_material = new Material();
}

Model2D::~Model2D()
{
    delete m_mesh;
    delete m_material;
}

void Model2D::OnUpdate(float dt)
{
    //Transformation

}

void Model2D::OnRender()
{
    m_material->Bind();
    m_mesh->Bind();
}
