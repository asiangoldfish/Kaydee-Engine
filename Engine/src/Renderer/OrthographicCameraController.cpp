#include "kdpch.h"
#include "OrthographicCameraController.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"

namespace Kaydee {
    OrthographicCameraController::OrthographicCameraController(
      float aspectRatio,
      bool rotation)
      : aspectRatio(aspectRatio)
      , camera(-aspectRatio * zoomLevel,
               aspectRatio * zoomLevel,
               -zoomLevel,
               zoomLevel)
      , enableRotation(rotation)
    {
    }

    void OrthographicCameraController::onUpdate(Timestep ts)
    {
        if (Input::isKeyPressed(KD_KEY_A)) {
            cameraPosition.x -= cameraTranslationSpeed * ts;
        }
        if (Input::isKeyPressed(KD_KEY_D)) {
            cameraPosition.x += cameraTranslationSpeed * ts;
        }
        if (Input::isKeyPressed(KD_KEY_W)) {
            cameraPosition.y += cameraTranslationSpeed * ts;
        }
        if (Input::isKeyPressed(KD_KEY_S)) {
            cameraPosition.y -= cameraTranslationSpeed * ts;
        }

        if (enableRotation) {
            if (Input::isKeyPressed(KD_KEY_Q)) {
                cameraRotation += cameraRotationSpeed * ts;
            }
            if (Input::isKeyPressed(KD_KEY_E)) {
                cameraRotation -= cameraRotationSpeed * ts;
            }
            camera.setRotation(cameraRotation);
        }

        camera.setPosition(cameraPosition);
        cameraTranslationSpeed = zoomLevel;
    }

    void OrthographicCameraController::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<MouseScrolledEvent>(
          KD_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
        dispatcher.dispatch<WindowResizeEvent>(
          KD_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
    }

    bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e)
    {
        zoomLevel -= e.getOffsetY() * 0.25f;
        zoomLevel = std::max(zoomLevel, 0.25f);
        camera.setProjection(-aspectRatio * zoomLevel,
                             aspectRatio * zoomLevel,
                             -zoomLevel,
                             zoomLevel);
        return false;
    }

    bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e)
    {
        aspectRatio = e.getWidth() / (float)e.getHeight();
        camera.setProjection(-aspectRatio * zoomLevel,
                             aspectRatio * zoomLevel,
                             -zoomLevel,
                             zoomLevel);
        return false;
    }
}