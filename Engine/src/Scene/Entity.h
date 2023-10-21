#pragma once

#include "Scene.h"

#include <entt/entt.hpp>
#include "Core/Core.h"

namespace Kaydee {

    /**
     * @description This class provides a set of convinient functions to the
     * EnTT library. Although entity components can be accessed through an
     * entity instance, the entity does not actually own this component.
     *
     * Entity is designed to be light weight and to be created and discarded
     * whenever needed. It should be allocated on the stack.
     */
    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);
        Entity(const Entity& other) = default;

        template<typename T, typename... Args>
        T& addComponent(Args&&... args)
        {
            KD_CORE_ASSERT(!hasComponent<T>(), "Entity already has component!");
            return scene->registry.emplace<T>(entityHandle,
                                              std::forward<Args>(args)...);
        }

        template<typename T>
        T& getComponent()
        {
            KD_CORE_ASSERT(hasComponent<T>(),
                           "Entity does not have component!");
            return scene->registry.get<T>(entityHandle);
        }

        template<typename T>
        bool hasComponent()
        {
            return scene->registry.any_of<T>(entityHandle);
        }

        template<typename T>
        void removeComponent()
        {
            KD_CORE_ASSERT(!hasComponent<T>(),
                           "Entity does not have component!");
            scene->registry.remove<T>(entityHandle);
        }

        operator bool() const { return entityHandle != entt::null; }
        operator uint32_t() const { return (uint32_t)entityHandle; }

        // Compare two entities
        bool operator==(const Entity& other) const
        {
            return entityHandle == other.entityHandle && scene == other.scene;
        }

        bool operator!=(const Entity& other) const
        {
            return !(*this == other);
        }

    private:
        entt::entity entityHandle = entt::null;
        Scene* scene = nullptr;
    };
}