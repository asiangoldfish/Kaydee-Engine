#pragma once

#include "Kaydee/Kaydee.h"
#include "SceneHierarchyPanel.h"

namespace Kaydee {
    /**
     * @brief 2D layer for Sandbox
     *
     */
    class EditorLayer : public Kaydee::Layer
    {
    public:
        EditorLayer();
        virtual ~EditorLayer() = default;

        virtual void onAttach() override;
        virtual void onDetach() override;
        void onUpdate(Kaydee::Timestep ts) override;
        virtual void onImGuiRender() override;
        void onEvent(Kaydee::Event& e) override;

    private:
        Kaydee::OrthographicCameraController cameraController;
        ref<Scene> activeScene;
        Entity squareEntity;
        Entity firstCameraEntity;
        Entity secondCameraEntity;

        Kaydee::ref<Kaydee::Framebuffer> framebuffer;
        glm::vec2 viewportSize = { 0.0f, 0.0f };
        bool viewportFocused = false;

        // Panels
        SceneHierarchyPanel sceneHierarchyPanel;
    };
}
