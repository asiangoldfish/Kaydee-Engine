#include "Core/Application.h"

#include <glad/glad.h>

#include "Core/Input.h"

// Temporary
#include "Renderer/Shader.h"

namespace Kaydee {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::instance = nullptr;

    Application::Application()
    {
        KD_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;

        window = std::unique_ptr<Window>(Window::create());

        // Event callback
        window->setEventCallback(BIND_EVENT_FN(onEvent));

        // ImGui
        imguiLayer = new ImGuiLayer();
        pushOverlay(imguiLayer);

        // Vertex array
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        float vertices[3 * 3] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                                  0.0f,  0.0f,  0.5f, 0.0f };

        vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
          0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        // Index buffer
        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

        unsigned int indices[3] = { 0, 1, 2 };
        glBufferData(
          GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertexShaderSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_position;

            out vec4 position;
            out vec3 v_position;

            void main() {
                v_position = a_position;
                gl_Position = vec4(a_position, 1);
            }
        )";

        std::string fragmentShaderSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec3 v_position;

            void main() {
                color = vec4(v_position * 0.5f + 0.5f, 1.0f);
            }
        )";

        shader.reset(new Shader(vertexShaderSrc, fragmentShaderSrc));
    }

    Application::~Application() {}

    void Application::run()
    {
        while (running) {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            shader->bind();
            glBindVertexArray(vertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : layerStack) {
                layer->onUpdate();
            }

            imguiLayer->begin();
            for (Layer* layer : layerStack) {
                layer->onImGuiRender();
            }
            imguiLayer->end();

            // auto [x, y] = Input::getMousePosition();
            //  KD_CORE_TRACE("{0}, {1}", x, y);

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