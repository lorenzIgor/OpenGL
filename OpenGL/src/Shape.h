#pragma once
#include "Interfaces/Transformable.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Shape : public Transformable
{
private:
    class VertexBuffer* m_vertexBuffer;
    class VertexArray* m_vertexArray;
    class IndexBuffer* m_indexBuffer;
    class VertexBufferLayout* m_layout;
    class Shader* m_shader;
    class Texture* m_texture;

    
    void Init();
public:
    Shape(const char* texture_path);
    Shape();
    ~Shape();

    void onDraw(glm::mat4 proj, glm::mat4 view) const ;
    VertexArray* getVertexArray() const { return m_vertexArray; }
    IndexBuffer* getIndexBuffer() const { return m_indexBuffer; }
    
    inline glm::mat4 getTransformMatrix() const { return glm::scale(glm::translate(glm::mat4(1.0f), this->getPosition()), this->getScale()); }
    inline Shader* getShader() const { return m_shader ; }
};
