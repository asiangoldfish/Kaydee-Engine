#include <Kaydee/Kaydee.h>
#include "Platforms/OpenGL/OpenGLShader.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem>
#include <cmath>

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

        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom left
            0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // Bottom right
            0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // Top right
            -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // Top left
        };

        Kaydee::ref<Kaydee::VertexBuffer> squareVB;
        squareVB.reset(
          Kaydee::VertexBuffer::create(squareVertices, sizeof(squareVertices)));

        squareVB->setLayout({
          { Kaydee::ShaderDataType::Float3, "a_position" },
          { Kaydee::ShaderDataType::Float2, "a_texCoord" },
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

        shader.reset(
          Kaydee::Shader::create(vertexShaderSrc, fragmentShaderSrc));

        std::string flatVertexSrc = R"(
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

        std::string flatFragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec3 v_position;
            uniform vec3 u_color;

            void main() {
                color = vec4(u_color, 1.0);
            }
        )";

        flatColorShader.reset(
          Kaydee::Shader::create(flatVertexSrc, flatFragmentSrc));

        std::string textureVertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec2 a_texCoord;

            out vec3 v_position;
            out vec2 v_texCoord;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

            void main() {
                v_texCoord = a_texCoord;
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
            }
        )";

        std::string textureFragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec2 v_texCoord;

            uniform vec3 u_color;
            uniform sampler2D u_texture;

            void main() {
                //color = vec4(v_texCoord, 0.0, 1.0);
                color = texture(u_texture, v_texCoord) * vec4(u_color, 1.0f);
            }
        )";

        textureShader.reset(
          Kaydee::Shader::create(textureVertexSrc, textureFragmentSrc));

        texture =
          Kaydee::Texture2D::create("Sandbox/assets/textures/checkerboard.png");

        pandaLogo =
          Kaydee::Texture2D::create("Sandbox/assets/textures/panda-face.png");

        flatColorShader->bind();
        std::dynamic_pointer_cast<Kaydee::OpenGLShader>(flatColorShader)
          ->uploadUniformInt("u_texture", 0);
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

            flatColorShader->bind();

            std::dynamic_pointer_cast<Kaydee::OpenGLShader>(flatColorShader)
              ->uploadUniformFloat3("u_color", squareColor);

            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < 20; j++) {
                    glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);

                    glm::mat4 transform =
                      glm::translate(glm::mat4(1.0f), pos) * scale;

                    Kaydee::Renderer::submit(
                      flatColorShader, squareVA, transform);
                }
            }

            textureShader->bind();
            texture->bind();

            std::dynamic_pointer_cast<Kaydee::OpenGLShader>(textureShader)
              ->uploadUniformFloat3("u_color", checkerColor);

            Kaydee::Renderer::submit(
              textureShader,
              squareVA,
              glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

            pandaLogo->bind();
            std::dynamic_pointer_cast<Kaydee::OpenGLShader>(textureShader)
              ->uploadUniformFloat3("u_color", pandaColor);
            Kaydee::Renderer::submit(
              textureShader,
              squareVA,
              glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

            // Triangle
            // Kaydee::Renderer::submit(shader, vertexArray);
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

    virtual void onImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor));
        ImGui::ColorEdit3("Checkerboard Color", glm::value_ptr(checkerColor));
        ImGui::ColorEdit3("Panda Color", glm::value_ptr(pandaColor));
        ImGui::End();
    }

private:
    Kaydee::ref<Kaydee::Shader> shader;
    Kaydee::ref<Kaydee::VertexArray> vertexArray;

    Kaydee::ref<Kaydee::Shader> flatColorShader, textureShader;
    Kaydee::ref<Kaydee::VertexArray> squareVA;

    Kaydee::ref<Kaydee::Texture2D> texture, pandaLogo;

    Kaydee::OrthographicCamera camera;
    glm::vec3 cameraPosition;
    float cameraMoveSpeed = 3.0f;
    float cameraRotation = 0.0f;
    float cameraRotationSpeed = 180.0f;

    glm::vec3 squareColor = { 0.2f, 0.3f, 0.8f },
              checkerColor = { 1.0f, 1.0f, 1.0f },
              pandaColor = { 1.0f, 1.0f, 1.0f };
};

class Sandbox : public Kaydee::Application
{
public:
    Sandbox()
    {
        std::cout << "Working directory: " << std::filesystem::current_path()
                  << std::endl;
        pushLayer(new ExampleLayer());
    }

    virtual ~Sandbox() {}
};

Kaydee::Application*
Kaydee::createApplication()
{
    return new Sandbox();
}