#include "Sandbox2D.h"

#include "Kaydee/Kaydee.h"
#include "imgui/imgui.h"
#include "Platforms/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
  : Kaydee::Layer("Sandbox2D")
  , cameraController(1280.0f / 720.0f, true)
{
}

void
Sandbox2D::onAttach()
{
    squareVA = Kaydee::VertexArray::create();

    float squareVertices[5 * 4] = {
        -0.5f, -0.5f, 0.0f, // Bottom left
        0.5f,  -0.5f, 0.0f, // Bottom right
        0.5f,  0.5f,  0.0f, // Top right
        -0.5f, 0.5f,  0.0f  // Top left
    };

    Kaydee::ref<Kaydee::VertexBuffer> squareVB;
    squareVB.reset(
      Kaydee::VertexBuffer::create(squareVertices, sizeof(squareVertices)));

    squareVB->setLayout({ { Kaydee::ShaderDataType::Float3, "a_position" } });

    squareVA->addVertexBuffer(squareVB);

    unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Kaydee::ref<Kaydee::IndexBuffer> squareIB;

    squareIB.reset(Kaydee::IndexBuffer::create(
      squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

    squareVA->setIndexBuffer(squareIB);

    flatColorShader =
      Kaydee::Shader::create("Sandbox/assets/shaders/flatColorShader.glsl");
}

void
Sandbox2D::onDetach()
{
}

void
Sandbox2D::onUpdate(Kaydee::Timestep ts)
{
    //------------
    // Update
    //------------
    cameraController.onUpdate(ts);

    //------------
    // Render
    //------------
    Kaydee::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Kaydee::RenderCommand::clear();

    Kaydee::Renderer::beginScene(cameraController.getCamera());
    {
        flatColorShader->bind();
        std::dynamic_pointer_cast<Kaydee::OpenGLShader>(flatColorShader)
          ->uploadUniformFloat4("u_color", squareColor);

        Kaydee::Renderer::submit(flatColorShader,
                                 squareVA,
                                 glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

        // Triangle
        // Kaydee::Renderer::submit(shader, vertexArray);
    }
    Kaydee::Renderer::endScene();
}

void
Sandbox2D::onImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
    ImGui::End();
}

void
Sandbox2D::onEvent(Kaydee::Event& e)
{
    cameraController.onEvent(e);
}