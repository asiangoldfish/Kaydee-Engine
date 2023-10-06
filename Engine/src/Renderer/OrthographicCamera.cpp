#include "Renderer/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include "OrthographicCamera.h"

namespace Kaydee {

    OrthographicCamera::OrthographicCamera(float left,
                                           float right,
                                           float bottom,
                                           float top)
      : projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
      , viewMatrix(1.0f)
    {
        KD_PROFILE_FUNCTION();

        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }

    void OrthographicCamera::setProjection(float left,
                                           float right,
                                           float bottom,
                                           float top)
    {
        KD_PROFILE_FUNCTION();

        projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }

    void OrthographicCamera::recalculateViewMatrix()
    {
        KD_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f),
                                          glm::radians(rotation),
                                          glm::vec3(0.0f, 0.0f, 1.0f));

        viewMatrix = glm::inverse(transform);
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }

}