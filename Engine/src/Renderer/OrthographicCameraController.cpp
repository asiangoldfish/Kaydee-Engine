#include "kdpch.h"
#include "OrthographicCameraController.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"

namespace Kaydee {
    OrthographicCameraController::OrthographicCameraController(
      float aspectRatio,
      bool rotation)
      : aspectRatio(aspectRatio)
      , cameraBounds(-aspectRatio * zoomLevel,
                     aspectRatio * zoomLevel,
                     -zoomLevel,
                     zoomLevel)
      , camera(cameraBounds.left,
               cameraBounds.right,
               cameraBounds.bottom,
               cameraBounds.top)
      , enableRotation(rotation)
    {
    }

    void OrthographicCameraController::onUpdate(Timestep ts)
    {
        KD_PROFILE_FUNCTION();

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
        KD_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.dispatch<MouseScrolledEvent>(
          KD_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
        dispatcher.dispatch<WindowResizeEvent>(
          KD_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
    }

    void OrthographicCameraController::calculateView()
    {
        cameraBounds = { -aspectRatio * zoomLevel,
                         aspectRatio * zoomLevel,
                         -zoomLevel,
                         zoomLevel };

        camera.setProjection(cameraBounds.left,
                             cameraBounds.right,
                             cameraBounds.bottom,
                             cameraBounds.top);
    }

    bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e)
    {
        KD_PROFILE_FUNCTION();

        zoomLevel -= e.getOffsetY() * 0.25f;
        zoomLevel = std::max(zoomLevel, 0.25f);
        calculateView();
        return false;
    }

    bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e)
    {
        KD_PROFILE_FUNCTION();

        onResize((float)e.getWidth(), (float)e.getHeight());
        return false;
    }

    void OrthographicCameraController::onResize(float width, float height)
    {
        aspectRatio = width / height;
        calculateView();
    }
}