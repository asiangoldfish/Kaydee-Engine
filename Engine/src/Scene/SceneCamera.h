#pragma once

#include "Renderer/Camera.h"

namespace Kaydee {
    class SceneCamera : public Camera
    {
    public:
        enum class ProjectionType
        {
            Perspective = 0, Orthographic
        };

    public:
        SceneCamera();
        virtual ~SceneCamera() = default;

        void setViewportSize(uint32_t width, uint32_t height);

        // ---------
        // Perspective
        // ---------
        void setPerspective(float verticalFov, float nearClip, float farClip);
        float getPerspectiveVerticalFOV() const { return perspectiveFOV; }
        void setPerspectiveVerticalFOV(float fov)
        {
            perspectiveFOV = fov;
            recalculateProjection();
        }
        float getPerspectiveNearClip() const { return perspectiveNear; }
        float getPerspectiveFarClip() const { return perspectiveFar; }
        void setPerspectiveNearClip(const float near)
        {
            perspectiveNear = near;
            recalculateProjection();
        }
        void setPerspectiveFarClip(const float far)
        {
            perspectiveFar = far;
            recalculateProjection();
        }

        // ---------
        // Orthographic
        // ---------
        void setOrthographic(float size, float nearClip, float farClip);
        float getOrthographicSize() const { return orthoSize; }
        void setOrthographicSize(float size)
        {
            orthoSize = size;
            recalculateProjection();
        }
        ProjectionType getProjectionType() const { return projectionType; }
        void setProjectionType(ProjectionType type) { projectionType = type; }
        float getOrthographicNearClip() const { return orthoNear; }
        float getOrthographicFarClip() const { return orthoFar; }
        void setOrthographicNearClip(const float near)
        {
            orthoNear = near;
            recalculateProjection();
        }
        void setOrthographicFarClip(const float far)
        {
            orthoFar = far;
            recalculateProjection();
        }

    private:
        void recalculateProjection();

    private:
        ProjectionType projectionType = ProjectionType::Orthographic;

        float aspectRatio = 1.0f;

        // Perspective properties
        float perspectiveFOV = glm::radians(45.0f);
        float perspectiveNear = 0.01f, perspectiveFar = 1000.0f;

        // Orthographic properties
        float orthoSize = 10.0f;
        float orthoNear = -1.0f, orthoFar = 1.0f;
    };
}