#pragma once

/**
 * All components live under this file
 */

#include "SceneCamera.h"
#include "ScriptableEntity.h"

#include <glm/glm.hpp>
#include <string>

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
        SceneCamera camera;
        bool primary = true;          // TODO: Think about moving to scene
        bool fixedAspectRatio = true; // If true, then this will not change if
                                      // the game viewport changes

        CameraComponent() = default;
        CameraComponent(const CameraComponent&) = default;
    };

    /**
     * @brief Support for native scripting with C++
     */
    struct NativeScriptComponent
    {
        /**
         * @brief When the runtime begins, the ScriptableEntity should be
         * instantiated.
         */
        ScriptableEntity* instance = nullptr;

        // Memory management handled by the engine
        ScriptableEntity* (*instantiateScript)();
        void (*destroyScript)(NativeScriptComponent*);

        template<typename T>
        void bind()
        {
            // Memory management handled by the engine
            instantiateScript = []() {
                return static_cast<ScriptableEntity*>(new T());
            };
            destroyScript = [](NativeScriptComponent* nsc) {
                if (nsc->instance) {
                    delete nsc->instance;
                    nsc->instance = nullptr;
                }
            };
        }
    };
}