#pragma once

#include "Renderer/OrthographicCamera.h"
#include "Core/Timestep.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

#include <glm/glm.hpp>

namespace Kaydee {
    struct OrthographicCameraBounds
    {
        float left, right;
        float bottom, top;

        inline float getWidth() { return right - left; }
        inline float getHeight() { return top - bottom; }

        OrthographicCameraBounds(float left,
                                 float right,
                                 float bottom,
                                 float top)
          : left(left)
          , right(right)
          , bottom(bottom)
          , top(top)
        {
        }
    };

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void onUpdate(Timestep ts);
        void onEvent(Event& e);

        void onResize(float width, float height);

        const OrthographicCameraBounds& getBounds() const
        {
            return cameraBounds;
        }

        OrthographicCamera& getCamera() { return camera; }
        const OrthographicCamera& getCamera() const { return camera; }

        float getZoomLevel() { return zoomLevel; }
        void setZoomLevel(const float level)
        {
            zoomLevel = level;
            calculateView();
        }

    private:
        void calculateView();

        bool onMouseScrolled(MouseScrolledEvent& e);
        bool onWindowResized(WindowResizeEvent& e);

    private:
        float aspectRatio;
        float zoomLevel = 1.0f;
        OrthographicCameraBounds cameraBounds;
        OrthographicCamera camera;

        bool enableRotation = false;

        glm::vec3 cameraPosition = { 0.f, 0.f, 0.f };
        float cameraRotation = 0.0f;
        float cameraTranslationSpeed = 2.5f, cameraRotationSpeed = 180.f;
    };

}
