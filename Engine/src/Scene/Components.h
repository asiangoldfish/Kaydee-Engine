#pragma once

/**
 * All components live under this file
 */

#include "SceneCamera.h"
#include "ScriptableEntity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
        glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::vec3& translation)
          : translation(translation)
        {
        }

        // TODO: implement a way to provide rotation in radians or degrees in
        // the UI
        glm::mat4 getTransform() const
        {
            // Construct rotation matrix
            glm::mat4 rotation =
              glm::rotate(glm::mat4(1.0f), this->rotation.x, { 1, 0, 0 }) *
              glm::rotate(glm::mat4(1.0f), this->rotation.y, { 0, 1, 0 }) *
              glm::rotate(glm::mat4(1.0f), this->rotation.z, { 0, 0, 1 });

            // Construct transformation matrix
            return glm::translate(glm::mat4(1.0f), translation) * rotation *
                   glm::scale(glm::mat4(1.0f), scale);
        }
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
        virtual ~CameraComponent() {}
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