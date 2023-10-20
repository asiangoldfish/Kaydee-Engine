#pragma once

/**
 * All components live under this file
 */

#include "Renderer/Camera.h"

#include <glm/glm.hpp>

namespace Kaydee {
    struct TagComponent
    {
        std::string tag;

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag)
          : tag(tag)
        {
        }
    };

    struct TransformComponent
    {
        glm::mat4 transform{ 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::mat4& transform)
          : transform(transform)
        {
        }

        operator glm::mat4&() { return transform; }
        operator const glm::mat4&() const { return transform; }
    };

    struct SpriteRendererComponent
    {
        glm::vec4 color{ 1.0f };

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const SpriteRendererComponent&) = default;
        SpriteRendererComponent(const glm::vec4& color)
          : color(color)
        {
        }
    };

    struct CameraComponent
    {
        Camera camera;
        bool primary = true; // TODO: Think about moving to scene

        CameraComponent() = default;
        CameraComponent(const CameraComponent&) = default;
        CameraComponent(const glm::mat4& projection)
          : camera(projection)
        {
        }
    };
}