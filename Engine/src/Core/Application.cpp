#include "Core/Application.h"

#include <glad/glad.h>

#include "Core/Input.h"

// Temporary
#include "Renderer/Shader.h"

namespace Kaydee {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::instance = nullptr;

    static GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type) {
            case ShaderDataType::Float:
                return GL_FLOAT;
            case ShaderDataType::Float2:
                return GL_FLOAT;
            case ShaderDataType::Float3:
                return GL_FLOAT;
            case ShaderDataType::Float4:
                return GL_FLOAT;
            case ShaderDataType::Mat3:
                return GL_FLOAT;
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
                return GL_INT;
            case ShaderDataType::Int2:
                return GL_INT;
            case ShaderDataType::Int3:
                return GL_INT;
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
        }

        KD_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

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

        float vertices[3 * 7] = { -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                  0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                                  0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f };

        vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

        {
            BufferLayout layout = { { ShaderDataType::Float3, "a_position" },
                                    { ShaderDataType::Float4, "a_color" } };

            vertexBuffer->setLayout(layout);
        }

        uint32_t index = 0;
        const auto& layout = vertexBuffer->getLayout();
        for (const auto& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  element.getComponentCount(),
                                  shaderDataTypeToOpenGLBaseType(element.type),
                                  element.normalized ? GL_TRUE : GL_FALSE,
                                  layout.getStride(),
                                  (const void*)element.offset);

            index++;
        }

        // Index buffer
        unsigned int indices[3] = { 0, 1, 2 };
        indexBuffer.reset(
          IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string vertexShaderSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec4 a_color;

            out vec3 v_position;
            out vec4 v_color;

            void main() {
                v_position = a_position;
                v_color = a_color;
                gl_Position = vec4(a_position, 1);
            }
        )";

        std::string fragmentShaderSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec3 v_position;
            in vec4 v_color;

            void main() {
                //color = vec4(v_position * 0.5f + 0.5f, 1.0f);
                color = v_color;
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
            glDrawElements(
              GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

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