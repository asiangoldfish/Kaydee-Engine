#ifndef __ORTHOGRAPHIC_CAMERA_CONTROLLER_H__
#define __ORTHOGRAPHIC_CAMERA_CONTROLLER_H__

#include "Renderer/OrthographicCamera.h"
#include "Core/Timestep.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

#include <glm/glm.hpp>

namespace Kaydee {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void onUpdate(Timestep ts);
        void onEvent(Event& e);

        OrthographicCamera& getCamera() { return camera; }
        const OrthographicCamera& getCamera() const { return camera; }

        float getZoomLevel() { return zoomLevel; }
        void setZoomLevel(const float level) { zoomLevel = level; }

    private:
        bool onMouseScrolled(MouseScrolledEvent& e);
        bool onWindowResized(WindowResizeEvent& e);

    private:
        float aspectRatio;
        float zoomLevel = 1.0f;
        OrthographicCamera camera;

        bool enableRotation = false;

        glm::vec3 cameraPosition = { 0.f, 0.f, 0.f };
        float cameraRotation = 0.0f;
        float cameraTranslationSpeed = 2.5f, cameraRotationSpeed = 180.f;
    };

}

#endif // __ORTHOGRAPHIC_CAMERA_CONTROLLER_H__