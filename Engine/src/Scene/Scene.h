#pragma once

#include "entt/entt.hpp"
#include "Core/Timestep.h"

namespace Kaydee {
    class Scene
    {
    public:
        Scene();
        virtual ~Scene();

        entt::entity createEntity();

        // TEMPORARY
        entt::registry& reg() { return registry; }

        void onUpdate(Timestep ts);

    private:
        entt::registry registry;
    };
}