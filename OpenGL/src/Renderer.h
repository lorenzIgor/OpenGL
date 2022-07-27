#pragma once

#include <GL/glew.h>
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

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
    void Clear() const;
    void ClearTranspatency() const;
    void Clear(float r, float g, float b) const;
    void Draw(const VertexArray& va, const IndexBuffer&, const Shader& shader) const;
    
};
