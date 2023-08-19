#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Core/Layer.h"
#include "Core/LayerStack.h"
#include "Core/Window.h"
#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

namespace Kaydee {
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();

        // Events
        void onEvent(Event& e);

        // Layers
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

        // ImGui
        ImGuiLayer* imguiLayer;

        // Application owns layer stack
        LayerStack layerStack;

        static Application* instance;
    };

    // To be defined in the client
    Application* createApplication();
}

#endif
