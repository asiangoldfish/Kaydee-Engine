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

    private:
        void drawEntityNode(Entity entity);

    private:
        ref<Scene> context;
        Entity selectionContext;
    };
}