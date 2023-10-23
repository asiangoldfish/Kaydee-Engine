#include "SceneCamera.h"
#include "kdpch.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Kaydee {
    SceneCamera::SceneCamera()
    {
        recalculateProjection();
    }

    void SceneCamera::setOrthographic(float size, float nearClip, float farClip)
    {
        projectionType = ProjectionType::Orthographic;
        orthoSize = size;
        orthoNear = nearClip;
        orthoFar = farClip;
        recalculateProjection();
    }

    void SceneCamera::setViewportSize(uint32_t width, uint32_t height)
    {
        aspectRatio = (float)width / (float)height;
        recalculateProjection();
    }

    void SceneCamera::setPerspective(float verticalFov,
                                     float nearClip,
                                     float farClip)
    {
        projectionType = ProjectionType::Perspective;
        perspectiveFOV = verticalFov;
        perspectiveNear = nearClip;
        perspectiveFar = farClip;
        recalculateProjection();
    }

    void SceneCamera::recalculateProjection()
    {

        if (projectionType == ProjectionType::Perspective) { // Perspective
            projection = glm::perspective(
              perspectiveFOV, aspectRatio, perspectiveNear, perspectiveFar);
        } else { // Orthographic
            float orthoLeft = -0.5f * aspectRatio * orthoSize;
            float orthoRight = 0.5f * aspectRatio * orthoSize;
            float orthoBottom = -0.5f * orthoSize;
            float orthoTop = 0.5f * orthoSize;

            projection = glm::ortho(orthoLeft,
                                    orthoRight,
                                    orthoBottom,
                                    orthoTop,
                                    orthoNear,
                                    orthoFar);
        }
    }
}