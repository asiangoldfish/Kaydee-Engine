#pragma once

#include <glm/glm.hpp>

namespace Kaydee {
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void setProjection(float left, float right, float bottom, float top);

        const glm::vec3& getPosition() const { return position; }
        void setPosition(const glm::vec3& position)
        {
            this->position = position;
            recalculateViewMatrix();
        }

        float getRotation() const { return rotation; }
        void setRotation(float rotation)
        {
            this->rotation = rotation;
            recalculateViewMatrix();
        }

        const glm::mat4& getProjectionMatrix() const
        {
            return projectionMatrix;
        }
        const glm::mat4& getViewMatrix() const { return viewMatrix; }
        const glm::mat4& getViewProjectionMatrix() const
        {
            return viewProjectionMatrix;
        }

    private:
        void recalculateViewMatrix();

    private:
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 viewProjectionMatrix;

        glm::vec3 position = { 0.0f, 0.0f, 0.0f };
        float rotation = 0.0f;
    };
}
