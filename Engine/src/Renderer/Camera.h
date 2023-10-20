#pragma once

#include <glm/glm.hpp>

namespace Kaydee {
    /**
     * @brief This camera is designed to work with components
    */
    class Camera
    {
    public:
        Camera(const glm::mat4& projection)
          : projection(projection)
        {
        }

        const glm::mat4& getProjection() const { return projection; }

    private:
        glm::mat4 projection;
    };
}