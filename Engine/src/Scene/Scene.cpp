#include "kdpch.h"
#include "Scene.h"

#include "Components.h"
#include "Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

namespace Kaydee {

    Scene::Scene() {}

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
        // ------------
        // Update scripts
        // ------------
        // Simulate creating and destroying instances
        {
            registry.view<NativeScriptComponent>().each(
              [=](auto entity, auto& nsc) {
                  // TODO: Move to Scene::onScenePlay(...)
                  if (!nsc.instance) {
                      nsc.instance = nsc.instantiateScript();
                      nsc.instance->entity = Entity{ entity, this };
                      nsc.instance->onCreate();
                  }

                  nsc.instance->onUpdate(ts);
              });
        }

        // ------------
        // Render sprites
        // ------------
        Camera* mainCamera = nullptr;
        glm::mat4* cameraTransform = nullptr;
        {
            auto view = registry.view<CameraComponent, TransformComponent>();
            // Try to find the main camera
            for (auto entity : view) {
                auto [camera, transform] =
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
                Renderer2D::drawQuad(
                  &Quad2DProperties{ transform, sprite.color });
            }

            Renderer2D::endScene();
        }
    }

    void Scene::onViewportResize(uint32_t width, uint32_t height)
    {
        viewportWidth = width;
        viewportHeight = height;

        // Resize our non-FixedAspectRatio cameras
        auto view = registry.view<CameraComponent>();
        // Try to find the main camera
        for (auto entity : view) {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if (!cameraComponent.fixedAspectRatio) {
                cameraComponent.camera.setViewportSize(width, height);
            }
        }
    }

}