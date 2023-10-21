#pragma once

#include "Renderer/Camera.h"

namespace Kaydee {
    class SceneCamera : public Camera
    {
    public:
        SceneCamera();
        virtual ~SceneCamera() = default;

        void setOrthographic(float size, float nearClip, float farClip);

        void setViewportSize(uint32_t width, uint32_t height);

        float getOrthographicSize() const { return orthoSize; }
        void setOrthographicSize(float size)
        {
            orthoSize = size;
            recalculateProjection();
        } 

    private:
        void recalculateProjection();

    private:
        float orthoSize = 10.0f;
        float orthoNear = -1.0f, orthoFar = 1.0f;

        float aspectRatio = 1.0f;
    };
}