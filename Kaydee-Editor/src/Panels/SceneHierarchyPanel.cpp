#include "SceneHierarchyPanel.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Scene/Components.h"

#include <array>
#include <typeinfo>

#include "imgui_internal.h"

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

    /**
     * @brief Draw a vec3 control with label on the left-hand side
     * @param label Label to display
     * @param values Editable values
     * @param resetValue Default value
     * @param columnWidth Width of the column between label and values
     */
    static void drawVec3Control(const std::string& label,
                                glm::vec3& values,
                                float resetValue = 0.0f,
                                float columnWidth = 100.0f)
    {
        // Add ID to distinguish between multiple ImGui components that invoke
        // this function
        ImGui::PushID(label.c_str());

        ImGui::Columns(2);

        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str()); // Label to display
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        const float lineHeight =
          GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        const ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        // --------------
        // Draw the ImGui elements...
        // --------------
        // X
        // TODO: Create UI library to store these color functions
        ImGui::PushStyleColor(ImGuiCol_Button,
                              ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                              ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                              ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        if (ImGui::Button("X", buttonSize)) {
            values.x = resetValue;
        }

        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        // Y
        ImGui::PushStyleColor(ImGuiCol_Button,
                              ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                              ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                              ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        if (ImGui::Button("Y", buttonSize)) {
            values.y = resetValue;
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        // Z
        ImGui::PushStyleColor(ImGuiCol_Button,
                              ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                              ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                              ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        if (ImGui::Button("Z", buttonSize)) {
            values.z = resetValue;
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        // Reset all values
        if (ImGui::Button("Reset", ImVec2{ lineHeight + 25.0f, lineHeight })) {
            values.x = resetValue;
            values.y = resetValue;
            values.z = resetValue;
        }

        ImGui::Columns(1);
        ImGui::PopStyleVar(1);
        ImGui::PopID();
    }

    void Kaydee::SceneHierarchyPanel::drawComponents(Entity entity)
    {
        // Tag component
        if (entity.hasComponent<TagComponent>()) {
            auto& tag = entity.getComponent<TagComponent>().tag;

            // Example: Camera0

            char buffer[256] = {};
            strcpy_s(buffer, sizeof(buffer), tag.c_str());
            if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
                tag = std::string(buffer);
            }
        } // Tag component end

        // Transform component
        drawComponent<TransformComponent>(
          "Transform", entity, [](Entity entity) {
              auto& tc = entity.getComponent<TransformComponent>();

              drawVec3Control("Translation", tc.translation);

              glm::vec3 rotation = glm::degrees(tc.rotation);
              drawVec3Control("Rotation", rotation);
              tc.rotation = glm::radians(rotation);

              drawVec3Control("Scale", tc.scale, 1.0f);
          }); // Transform component end

        // Camera component
        drawComponent<CameraComponent>("Camera", entity, [](Entity entity) {
            auto& cameraComponent = entity.getComponent<CameraComponent>();

            ImGui::Checkbox("Primary", &cameraComponent.primary);

            const std::array<std::string, 2> projectionTypeStrings = {
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
                    const bool isSelected =
                      currentProjectionTypeString == projectionTypeStrings[i];

                    if (ImGui::Selectable(projectionTypeStrings[i].c_str(),
                                          isSelected)) {
                        currentProjectionTypeString = projectionTypeStrings[i];
                        cameraComponent.camera.setProjectionType(
                          static_cast<SceneCamera::ProjectionType>(i));
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
