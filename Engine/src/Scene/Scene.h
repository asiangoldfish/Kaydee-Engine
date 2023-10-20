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

    private:
        entt::registry registry;

        friend class Entity;
    };
}