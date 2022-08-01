#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Model2D.h"
#include "Renderer.h"

#include "Shape.h"


Renderer::Renderer()
{
    GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL))
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
    GLCall(glEnable(GL_BLEND))

    proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f);
    view = translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f ,0.0f));
}

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ") -> " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
}

void Renderer::ClearTranspatency() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Renderer::Clear(float r, float g, float b) const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(r, g, b, 1.0f);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCout(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const
{
    shader->Bind();
    va->Bind();
    ib->Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib->GetCout(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const Shape* shape) const
{
    shape->onDraw(proj, view);
    GLCall(glDrawElements(GL_TRIANGLES, shape->getIndexBuffer()->GetCout(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw() const
{
    for(const auto& shape : m_shapes){
        shape->onDraw(proj, view);
        GLCall(glDrawElements(GL_TRIANGLES, shape->getIndexBuffer()->GetCout(), GL_UNSIGNED_INT, nullptr));
    }
}

void Renderer::AddShape(Shape* shape)
{
    if(shape)
        m_shapes.push_back(shape);
}
