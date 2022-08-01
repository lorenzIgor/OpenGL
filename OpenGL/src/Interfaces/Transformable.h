#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Transformable
{
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec3 speed;
public:
    glm::vec3 getPosition() const
    {
        return position;
    }

    void setPosition(const glm::vec3& position)
    {
        this->position = position;
    }

    glm::vec3 getRotation() const
    {
        return rotation;
    }

    void setRotation(const glm::vec3& rotation)
    {
        this->rotation = rotation;
    }

    glm::vec3 getScale() const
    {
        return scale;
    }

    void setScale(const glm::vec3& scale)
    {
        this->scale = scale;
    }

    glm::vec3 getSpeed() const
    {
        return speed;
    }

    void setSpeed(const glm::vec3& speed)
    {
        this->speed = speed;
    }
};
