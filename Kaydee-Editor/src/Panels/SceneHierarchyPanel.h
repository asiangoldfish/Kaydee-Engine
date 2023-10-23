#pragma once

#include "Core/Core.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"

namespace Kaydee {
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const ref<Scene>& context);

        void setContext(const ref<Scene>& context);

        void onImGuiRender();

        template<class T>
        void drawComponent(const std::string& label,
                           Entity& entity, 
                           std::function<void(Entity& entity)> func);

    private:
        void drawEntityNode(Entity entity);

        /**
         * @brief Draw an entity's properties
         * @param entity Entity to display and manipulate
        */
        void drawComponents(Entity entity);

    private:
        ref<Scene> context;
        Entity selectionContext;
    };
}