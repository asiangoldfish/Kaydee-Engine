#pragma once

#include <glm/glm.hpp>

namespace Kaydee {
    /**
     * @brief This camera is designed to work with components
    */
    class Camera
    {
    public:
        Camera() = default;
        Camera(const glm::mat4& projection)
          : projection(projection)
        {
        }

        virtual ~Camera() = default;

        const glm::mat4& getProjection() const { return projection; }

    protected:
        glm::mat4 projection{ 1.0f };
    };
}