#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Core/Layer.h"
#include "Core/LayerStack.h"
#include "Core/Window.h"
#include "Events/ApplicationEvent.h"

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

    private:
        bool onWindowClose(WindowCloseEvent& e);

    private:
        std::unique_ptr<Window> window;
        bool running = true;

        // Application owns layer stack
        LayerStack layerStack;
    };

    // To be defined in the client
    Application* createApplication();
}

#endif
