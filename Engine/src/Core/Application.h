#pragma once

#include "Core/Layer.h"
#include "Core/LayerStack.h"
#include "Core/Window.h"
#include "Events/ApplicationEvent.h"
#include "Core/Timestep.h"

#include "ImGui/ImGuiLayer.h"

// Temporary
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

#include "Renderer/OrthographicCamera.h"

namespace Kaydee {
    class Application
    {
    public:
        Application(const std::string& name = "Kaydee App");
        virtual ~Application();

        void run();

        // Events
        void onEvent(Event& e);

        // Layersand there's to go about it
        void pushLayer(Layer* layer);

        void pushOverlay(Layer* overlay);

        // Window
        inline Window& getWindow() { return *window; }

        void close();

        ImGuiLayer* getImGuiLayer() { return imguiLayer; }

        // Singleton
        inline static Application& get() { return *instance; }

    private:
        bool onWindowClose(WindowCloseEvent& e);
        bool onWindowResize(WindowResizeEvent& e);
        // When the window is minimized
        bool onWindowIconify(WindowIconifyEvent& e);

    private:
        std::unique_ptr<Window> window;
        bool running = true;
        bool minimized = false;

        // Layers
        ImGuiLayer* imguiLayer;
        LayerStack layerStack;
        float lastFrameTime = 0.0f;

    private:
        static Application* instance;
    };

    // To be defined in the client
    Application* createApplication();
}
