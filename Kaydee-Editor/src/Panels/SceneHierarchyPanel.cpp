#include "SceneHierarchyPanel.h"

#include <imgui.h>

#include "Scene/Components.h"

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

            /*
            auto& tc = entity.getComponent<TagComponent>();
            ImGui::Text("%s", tc.tag.c_str());
            */
        });

        ImGui::End();
    }

    void SceneHierarchyPanel::drawEntityNode(Entity entity)
    {
        auto& tag = entity.getComponent<TagComponent>().tag;

        ImGuiTreeNodeFlags flags =
          ((selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
          ImGuiTreeNodeFlags_OpenOnArrow;
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
}