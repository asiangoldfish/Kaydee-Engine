#include <Kaydee/Kaydee.h>
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Kaydee::Layer
{
public:
    ExampleLayer()
      : Layer("Example")
      , camera(-1.6f, 1.6f, -0.9f, 0.9f)
      , cameraPosition(0.0f)
    {
        vertexArray.reset(Kaydee::VertexArray::create());

        float vertices[3 * 7] = { -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                  0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                                  0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f };

        Kaydee::ref<Kaydee::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(
          Kaydee::VertexBuffer::create(vertices, sizeof(vertices)));

        Kaydee::BufferLayout layout = {
            { Kaydee::ShaderDataType::Float3, "a_position" },
            { Kaydee::ShaderDataType::Float4, "a_color" }
        };

        vertexBuffer->setLayout(layout);
        vertexArray->addVertexBuffer(vertexBuffer);

        // Index buffer
        unsigned int indices[3] = { 0, 1, 2 };
        Kaydee::ref<Kaydee::IndexBuffer> indexBuffer;
        indexBuffer.reset(Kaydee::IndexBuffer::create(
          indices, sizeof(indices) / sizeof(uint32_t)));
        vertexArray->setIndexBuffer(indexBuffer);

        squareVA.reset(Kaydee::VertexArray::create());

        float squareVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.5f,  -0.5f, 0.0f,
            0.5f,  0.5f,  0.0f, -0.5f, 0.5f,  0.0f
        };

        Kaydee::ref<Kaydee::VertexBuffer> squareVB;
        squareVB.reset(
          Kaydee::VertexBuffer::create(squareVertices, sizeof(squareVertices)));

        squareVB->setLayout({
          { Kaydee::ShaderDataType::Float3, "a_position" },
        });

        squareVA->addVertexBuffer(squareVB);

        unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Kaydee::ref<Kaydee::IndexBuffer> squareIB;

        squareIB.reset(Kaydee::IndexBuffer::create(
          squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

        squareVA->setIndexBuffer(squareIB);

        std::string vertexShaderSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec4 a_color;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

            out vec3 v_position;
            out vec4 v_color;

            void main() {
                v_position = a_position;
                v_color = a_color;
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 1);
            }
        )";

        std::string fragmentShaderSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec3 v_position;
            in vec4 v_color;

            void main() {
                color = vec4(v_position * 0.5 + 0.5, 1.0);
                //color = v_color;
            }
        )";

        shader.reset(new Kaydee::Shader(vertexShaderSrc, fragmentShaderSrc));

        std::string blueVertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_position;

            out vec3 v_position;
            out vec4 v_color;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

            void main() {
                v_position = a_position;
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
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

        blueShader.reset(new Kaydee::Shader(blueVertexSrc, blueFragmentSrc));
    }

    void onUpdate(Kaydee::Timestep ts) override
    {
        // KD_TRACE(
        //   "Delta time: {0}s ({1}ms)", ts.getSeconds(), ts.getMilliseconds());

        // Move camera
        if (Kaydee::Input::isKeyPressed(KD_KEY_A)) {
            cameraPosition.x -= cameraMoveSpeed * ts;
        }
        if (Kaydee::Input::isKeyPressed(KD_KEY_D)) {
            cameraPosition.x += cameraMoveSpeed * ts;
        }
        if (Kaydee::Input::isKeyPressed(KD_KEY_W)) {
            cameraPosition.y += cameraMoveSpeed * ts;
        }
        if (Kaydee::Input::isKeyPressed(KD_KEY_S)) {
            cameraPosition.y -= cameraMoveSpeed * ts;
        }

        if (Kaydee::Input::isKeyPressed(KD_KEY_Q)) {
            cameraRotation -= cameraRotationSpeed * ts;
        }
        if (Kaydee::Input::isKeyPressed(KD_KEY_E)) {
            cameraRotation += cameraRotationSpeed * ts;
        }

        Kaydee::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Kaydee::RenderCommand::clear();

        camera.setRotation(cameraRotation);
        camera.setPosition(cameraPosition);

        Kaydee::Renderer::beginScene(camera);
        {
            static glm::mat4 scale =
              glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < 20; j++) {
                    glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);

                    glm::mat4 transform =
                      glm::translate(glm::mat4(1.0f), pos) * scale;

                    Kaydee::Renderer::submit(blueShader, squareVA, transform);
                }
            }

            Kaydee::Renderer::submit(shader, vertexArray);
            Kaydee::Renderer::submit(shader, vertexArray);
        }
        Kaydee::Renderer::endScene();
    }

    void onEvent(Kaydee::Event& event) override
    {
        Kaydee::EventDispatcher dispatcher(event);
        dispatcher.dispatch<Kaydee::KeyPressedEvent>(
          KD_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
    }

    bool OnKeyPressedEvent(Kaydee::KeyPressedEvent& event) { return false; }

    virtual void onImGuiRender() override {}

private:
    Kaydee::ref<Kaydee::Shader> shader;
    Kaydee::ref<Kaydee::VertexArray> vertexArray;

    Kaydee::ref<Kaydee::Shader> blueShader;
    Kaydee::ref<Kaydee::VertexArray> squareVA;

    Kaydee::OrthographicCamera camera;
    glm::vec3 cameraPosition;
    float cameraMoveSpeed = 3.0f;
    float cameraRotation = 0.0f;
    float cameraRotationSpeed = 180.0f;
};

class Sandbox : public Kaydee::Application
{
public:
    Sandbox() { pushLayer(new ExampleLayer()); }

    virtual ~Sandbox() {}
};

Kaydee::Application*
Kaydee::createApplication()
{
    return new Sandbox();
}