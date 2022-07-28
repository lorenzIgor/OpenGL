#pragma once

#include "Material.h"
#include "Mesh2D.h"
#include "Interfaces/Transformable.h"

class Mesh2D;
class Material;

class Model2D : public Transformable
{
private:
    Mesh2D*     m_mesh;
    Material*   m_material;
    glm::mat4   m_transformation;
    float       m_zIndex;           //Rendering priority
public:

    Model2D();
    ~Model2D();
    void OnUpdate(float dt);
    void OnRender();

    Mesh2D* getMesh() const { return m_mesh; }
    Material* getMaterial() const { return m_material; }
    glm::mat4 getMatrix() const {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), this->getPosition());
        // model = glm::translate(m_modelMatrix, this->get_rotation());
        model =  glm::scale(model, this->getScale());
        return model;
    }
};
