#pragma once

class VertexBufferLayout;

class Mesh2D
{
private:
    class VertexArray* m_vertexArray;
    class IndexBuffer* m_indexBuffer;
    class VertexBuffer* m_vertexBuffer;
    class VertexBufferLayout* m_layout;
public:
    Mesh2D();
    ~Mesh2D();
    
    void Bind();
    void Unbind();

    VertexArray* getVertexArray() const { return m_vertexArray; }
    IndexBuffer* getIndexBuffer() const { return m_indexBuffer; }
};
