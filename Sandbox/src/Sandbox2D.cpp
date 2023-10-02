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

    Kaydee::Renderer2D::beginScene(cameraController.getCamera());
    {
        // flatColorShader->bind();
        //  TODO: Add the functions: Shader::SetMat4, Shader::SetFloat4
        //  std::dynamic_pointer_cast<Kaydee::OpenGLShader>(flatColorShader)
        //   ->uploadUniformFloat4("u_color", squareColor);
        //
        //  Kaydee::Renderer::submit(flatColorShader,
        //                          squareVA,
        //                          glm::scale(glm::mat4(1.0f),
        //                          glm::vec3(1.0f)));

        // Triangle
        // Kaydee::Renderer::submit(shader, vertexArray);

        Kaydee::Renderer2D::drawQuad(
          { 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 0.2f, 0.2f, 1.0f });
    }
    Kaydee::Renderer2D::endScene();
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