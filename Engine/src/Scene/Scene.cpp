#include "kdpch.h"
#include "Scene.h"

#include "Components.h"
#include "Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Kaydee {

    Scene::Scene()
    {
#if ENTT_EXAMPLE_CODE
        entt::entity entity = registry.create();
        registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

        auto view = registry.view<TransformComponent>();
        for (auto entity : view) {
            TransformComponent& transform =
              view.get<TransformComponent>(entity);
        }

        auto group =
          registry.group<TransformComponent>(entt::get<MeshComponent>);
        for (auto entity : group) {
            auto& [transform, mesh] =
              group.get<TransformComponent, MeshComponent>(entity);

            // Renderer::submit(mesh, transform
        }
#endif
    }

    Scene::~Scene() {}

    entt::entity Scene::createEntity()
    {
        return registry.create();
    }

    void Scene::onUpdate(Timestep ts)
    {
        auto group = registry.group<TransformComponent>(
          entt::get<SpriteRendererComponent>);
        for (auto entity : group) {
            auto& [transform, sprite] =
              group.get<TransformComponent, SpriteRendererComponent>(entity);
            Quad2DProperties props = { transform, sprite.color };
            Renderer2D::drawQuad(&props);
        }
    }
}