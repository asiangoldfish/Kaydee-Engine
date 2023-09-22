#include "Core/Application.h"

#include "Core/Input.h"
#include "Renderer/Renderer.h"

namespace Kaydee {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::instance = nullptr;

    Application::Application()
      : camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        KD_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;

        window = std::unique_ptr<Window>(Window::create());

        // Event callback
        window->setEventCallback(BIND_EVENT_FN(onEvent));

        // ImGui
        imguiLayer = new ImGuiLayer();
        pushOverlay(imguiLayer);

        vertexArray.reset(VertexArray::create());

        float vertices[3 * 7] = { -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                  0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                                  0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f };

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

        BufferLayout layout = { { ShaderDataType::Float3, "a_position" },
                                { ShaderDataType::Float4, "a_color" } };

        vertexBuffer->setLayout(layout);
        vertexArray->addVertexBuffer(vertexBuffer);

        // Index buffer
        unsigned int indices[3] = { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(
          IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
        vertexArray->setIndexBuffer(indexBuffer);

        squareVA.reset(VertexArray::create());

        float squareVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.5f,  -0.5f, 0.0f,
            0.5f,  0.5f,  0.0f, -0.5f, 0.5f,  0.0f
        };

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(
          VertexBuffer::create(squareVertices, sizeof(squareVertices)));

        squareVB->setLayout({
          { ShaderDataType::Float3, "a_position" },
        });

        squareVA->addVertexBuffer(squareVB);

        unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> squareIB;

        squareIB.reset(IndexBuffer::create(
          squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

        squareVA->setIndexBuffer(squareIB);

        std::string vertexShaderSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec4 a_color;

            uniform mat4 u_viewProjection;

            out vec3 v_position;
            out vec4 v_color;

            void main() {
                v_position = a_position;
                v_color = a_color;
                gl_Position = u_viewProjection * vec4(a_position, 1);
            }
        )";

        std::string fragmentShaderSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec3 v_position;
            in vec4 v_color;

            void main() {
                color = vec4(v_position * 0.5f + 0.5f, 1.0f);
                //color = v_color;
            }
        )";

        shader.reset(new Shader(vertexShaderSrc, fragmentShaderSrc));

        std::string blueVertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_position;

            out vec3 v_position;
            out vec4 v_color;

            uniform mat4 u_viewProjection;

            void main() {
                v_position = a_position;
                gl_Position = u_viewProjection * vec4(a_position, 1);
            }
        )";

        std::string blueFragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec3 v_position;

            void main() {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";

        blueShader.reset(new Shader(blueVertexSrc, blueFragmentSrc));
    }

    Application::~Application() {}

    void Application::run()
    {
        while (running) {
            RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            RenderCommand::clear();

            // camera.setPosition({ 0.5f, 0.5f, 0.0f });
            camera.setPosition({ 0.5f, 0.5f, 0 });
            camera.setRotation(45.0f);

            Renderer::beginScene(camera);
            {
                Renderer::submit(blueShader, squareVA);
                Renderer::submit(shader, vertexArray);
            }
            Renderer::endScene();

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