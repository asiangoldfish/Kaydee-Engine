#pragma once

#include <entt/entt.hpp>
#include "Core/Timestep.h"

namespace Kaydee {
    class Entity;

    class Scene
    {
    public:
        Scene();
        virtual ~Scene();

        Entity createEntity(const std::string& name = std::string());

        void onUpdate(Timestep ts);
        void onViewportResize(uint32_t width, uint32_t height);

    private:
        friend class Entity;
        friend class SceneHierarchyPanel;

        entt::registry registry;

        uint32_t viewportWidth = 0, viewportHeight = 0;
    };
}