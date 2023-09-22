#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Core/Layer.h"
#include "Core/LayerStack.h"
#include "Core/Window.h"
#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

// Temporary
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

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
        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);

        // Window
        inline Window& getWindow() { return *window; }

        // Singleton
        inline static Application& get() { return *instance; }

    private:
        bool onWindowClose(WindowCloseEvent& e);

    private:
        std::unique_ptr<Window> window;
        bool running = true;

        // Layers
        ImGuiLayer* imguiLayer;
        LayerStack layerStack;

        std::shared_ptr<Shader> shader;
        std::shared_ptr<VertexArray> vertexArray;

        std::shared_ptr<Shader> blueShader;
        std::shared_ptr<VertexArray> squareVA;


    private:
        static Application* instance;
    };

    // To be defined in the client
    Application* createApplication();
}

#endif
