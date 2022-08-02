#pragma once

#include <GL/glew.h>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

class Shape;
class Model2D;
class VertexArray;
class IndexBuffer;
class Shader;

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x)\
GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    Renderer();

    void Clear() const;
    void ClearTranspatency() const;
    void Clear(float r, float g, float b) const;
    
    void Draw(const VertexArray& va, const IndexBuffer&, const Shader& shader) const;
    void Draw(const VertexArray* va, const IndexBuffer*, const Shader* shader) const;
    void Draw(const Shape* shape) const;
    void Draw() const;
  
    void AddShape(Shape* shape);

    std::vector<Shape*> getShapes() const
    {
        return m_shapes;
    }

private:
    std::vector<Shape*> m_shapes;
    glm::mat4 proj;
    glm::mat4 view;
};
