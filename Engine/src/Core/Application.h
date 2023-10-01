#ifndef __APPLICATION_H__
#define __APPLICATION_H__

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
        Application();
        virtual ~Application();

        void run();

        // Events
        void onEvent(Event& e);

        // Layersand there's to go about it
        inline void pushLayer(Layer* layer)
        {
            layerStack.pushLayer(layer);
            layer->onAttach();
        }

        inline void pushOverlay(Layer* overlay)
        {
            layerStack.pushOverlay(overlay);
            overlay->onAttach();
        }

        // Window
        inline Window& getWindow() { return *window; }

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

#endif
