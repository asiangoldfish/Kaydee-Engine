#include "kdpch.h"
#include "Scene.h"

#include "Components.h"
#include "Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

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

    Entity Scene::createEntity(const std::string& name)
    {
        Entity entity = { registry.create(), this };
        entity.addComponent<TransformComponent>();
        auto& tag = entity.addComponent<TagComponent>();
        tag.tag = name.empty() ? "Entity" : name;

        return entity;
    }

    void Scene::onUpdate(Timestep ts)
    {
        // Render sprites
        Camera* mainCamera = nullptr;
        glm::mat4* cameraTransform = nullptr;
        {
            auto view = registry.view<CameraComponent, TransformComponent>();
            // Try to find the main camera
            for (auto entity : view) {
                auto& [camera, transform] =
                  registry.get<CameraComponent, TransformComponent>(entity);

                if (camera.primary) {
                    mainCamera = &camera.camera;
                    cameraTransform = &transform.transform;
                    break;
                }
            }
        }

        if (mainCamera) {
            Renderer2D::beginScene(mainCamera->getProjection(),
                                   *cameraTransform);

            auto group = registry.group<TransformComponent>(
              entt::get<SpriteRendererComponent>);
            for (auto entity : group) {
                auto& [transform, sprite] =
                  group.get<TransformComponent, SpriteRendererComponent>(
                    entity);
                Quad2DProperties props = { transform, sprite.color };
                Renderer2D::drawQuad(&props);
            }

            Renderer2D::endScene();
        }
    }
}