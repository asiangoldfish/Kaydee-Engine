#include "SceneHierarchyPanel.h"
#include "SceneHierarchyPanel.h"

#include <imgui.h>

#include "Scene/Components.h"

#include <glm/gtc/type_ptr.hpp>

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
        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
        {
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

    void Kaydee::SceneHierarchyPanel::drawComponents(Entity entity)
    {
        if (entity.hasComponent<TagComponent>()) {
            auto& tag = entity.getComponent<TagComponent>().tag;

            // Example: Camera0

            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), tag.c_str());
            if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
                tag = std::string(buffer);
            }
        }

        if (entity.hasComponent<TransformComponent>()) {
            if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(),
                                  ImGuiTreeNodeFlags_DefaultOpen,
                                  "Transform")) {
                auto& transform =
                  entity.getComponent<TransformComponent>().transform;
                ImGui::DragFloat3(
                  "Position", glm::value_ptr(transform[3]), 0.1f);

                ImGui::TreePop();
            }
        }
    }
}