#include "SceneHierarchyPanel.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Scene/Components.h"

#include <array>
#include <typeinfo>

namespace Kaydee {
    SceneHierarchyPanel::SceneHierarchyPanel(const ref<Scene>& context)
    {
        setContext(context);
    }

    void SceneHierarchyPanel::setContext(const ref<Scene>& context)
    {
        this->context = context;
    }

    void SceneHierarchyPanel::onImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");

        context->registry.each([&](auto entityID) {
            Entity entity{ entityID, context.get() };
            drawEntityNode(entity);
        });

        // Deselect nodes
        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
            selectionContext = {};
        }

        ImGui::End();

        // Property panel for entites
        ImGui::Begin("Properties");
        {
            if (selectionContext) {
                drawComponents(selectionContext);
            }
        }
        ImGui::End();
    }

    void SceneHierarchyPanel::drawEntityNode(Entity entity)
    {
        auto& tag = entity.getComponent<TagComponent>().tag;

        ImGuiTreeNodeFlags flags =
          ((selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
          ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        bool opened = ImGui::TreeNodeEx(
          (void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

        // Respond to node being clicked
        if (ImGui::IsItemClicked()) {
            selectionContext = entity;
        }

        if (opened) {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened =
              ImGui::TreeNodeEx((void*)46546131, flags, tag.c_str());
            if (opened) {
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }

    template<class T>
    void SceneHierarchyPanel::drawComponent(
      const std::string& label,
      Entity& entity,
      std::function<void(Entity& entity)> func)
    {
        if (entity.hasComponent<T>()) {
            if (ImGui::TreeNodeEx((void*)typeid(T).hash_code(),
                                  ImGuiTreeNodeFlags_DefaultOpen,
                                  label.c_str())) {
                func(entity);
                ImGui::TreePop();
            }
        }
    }

    void Kaydee::SceneHierarchyPanel::drawComponents(Entity entity)
    {
        // Tag component
        if (entity.hasComponent<TagComponent>()) {
            auto& tag = entity.getComponent<TagComponent>().tag;

            // Example: Camera0

            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), tag.c_str());
            if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
                tag = std::string(buffer);
            }
        } // Tag component end

        // Transform component
        drawComponent<TransformComponent>(
          "Transform", entity, [](Entity entity) {
              auto& transform =
                entity.getComponent<TransformComponent>().transform;
              ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);
          }); // Transform component end

        // Camera component
        drawComponent<CameraComponent>("Camera", entity, [](Entity entity) {
            auto& cameraComponent = entity.getComponent<CameraComponent>();

            ImGui::Checkbox("Primary", &cameraComponent.primary);

            std::array<std::string, 2> projectionTypeStrings = {
                "Perspective", "Orthographic"
            };
            std::string currentProjectionTypeString =
              projectionTypeStrings[(int)cameraComponent.camera
                                      .getProjectionType()];

            ImGui::Text("Projection");
            ImGui::SameLine();
            if (ImGui::BeginCombo("##Projection",
                                  currentProjectionTypeString.c_str())) {
                for (int i = 0; i < 2; i++) {
                    bool isSelected =
                      currentProjectionTypeString == projectionTypeStrings[i];

                    if (ImGui::Selectable(projectionTypeStrings[i].c_str(),
                                          isSelected)) {
                        currentProjectionTypeString = projectionTypeStrings[i];
                        cameraComponent.camera.setProjectionType(
                          (SceneCamera::ProjectionType)i);
                    }

                    if (isSelected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            if (cameraComponent.camera.getProjectionType() ==
                SceneCamera::ProjectionType::Perspective) {
                float verticalFOV = glm::degrees(
                  cameraComponent.camera.getPerspectiveVerticalFOV());
                ImGui::Text("Vertical FOV");
                ImGui::SameLine();
                if (ImGui::DragFloat("##Vertical FOV", &verticalFOV)) {
                    cameraComponent.camera.setPerspectiveVerticalFOV(
                      glm::radians(verticalFOV));
                }

                float perspectiveNear =
                  cameraComponent.camera.getPerspectiveNearClip();
                ImGui::Text("Near");
                ImGui::SameLine();
                if (ImGui::DragFloat("##Near", &perspectiveNear)) {
                    cameraComponent.camera.setPerspectiveNearClip(
                      perspectiveNear);
                }

                float perspectiveFar =
                  cameraComponent.camera.getPerspectiveFarClip();
                ImGui::Text("Far");
                ImGui::SameLine();
                if (ImGui::DragFloat("##Far", &perspectiveFar)) {
                    cameraComponent.camera.setPerspectiveFarClip(
                      perspectiveFar);
                }
            }

            if (cameraComponent.camera.getProjectionType() ==
                SceneCamera::ProjectionType::Orthographic) {
                float orthoSize = cameraComponent.camera.getOrthographicSize();
                if (ImGui::DragFloat("Size", &orthoSize)) {
                    cameraComponent.camera.setOrthographicSize(orthoSize);
                }

                float orthoNear =
                  cameraComponent.camera.getOrthographicNearClip();
                if (ImGui::DragFloat("Near", &orthoNear)) {
                    cameraComponent.camera.setOrthographicNearClip(orthoNear);
                }

                float orthoFar =
                  cameraComponent.camera.getOrthographicFarClip();
                if (ImGui::DragFloat("Far", &orthoFar)) {
                    cameraComponent.camera.setOrthographicFarClip(orthoFar);
                }

                ImGui::Checkbox("Fixed Aspect Ratio",
                                &cameraComponent.fixedAspectRatio);
            }
        }); // Camera component end

        // Sprite Renderer component
        drawComponent<SpriteRendererComponent>(
          "Sprite Renderer", entity, [](Entity entity) {
              auto& src = entity.getComponent<SpriteRendererComponent>();
              ImGui::ColorEdit4("Color", glm::value_ptr(src.color));
          }); // Sprite component end
    }

}
