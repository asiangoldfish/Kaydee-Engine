#include "Core/Application.h"

#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Kaydee {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::instance = nullptr;

    Application::Application()
    {
        KD_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;

        window = std::unique_ptr<Window>(Window::create());
        window->setEventCallback(BIND_EVENT_FN(onEvent)); // Event callback
        //window->setVSync(true);

        Renderer::init();

        // ImGui
        imguiLayer = new ImGuiLayer();
        pushOverlay(imguiLayer);
    }

    Application::~Application() {}

    void Application::run()
    {
        while (running) {
            // Compute delta time
            float time = (float)glfwGetTime(); // Should be in Platform::GetTime
            Timestep timestep = time - lastFrameTime;
            lastFrameTime = time;

            for (Layer* layer : layerStack) {
                layer->onUpdate(timestep);
            }

            imguiLayer->begin();
            for (Layer* layer : layerStack) {
                layer->onImGuiRender();
            }
            imguiLayer->end();

            window->onUpdate();
        }
    }

    void Application::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

        // This prevents a handled event to be propagated backward
        for (auto it = layerStack.end(); it != layerStack.begin();) {
            (*--it)->onEvent(e);
            if (e.handled) {
                break;
            }
        }
    }

    bool Application::onWindowClose(WindowCloseEvent& e)
    {
        running = false;
        return true;
    }

    void Application::pushLayer(Layer* layer)
    {
        layerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer* overlay)
    {
        layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }
}