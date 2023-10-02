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
    checkerboardTexture =
      Kaydee::Texture2D::create("Sandbox/assets/textures/checkerboard.png");
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
        Kaydee::Renderer2D::drawQuad(
          { -1.0f, 0.0f }, { .8f, .8f }, 0.0f, { .8f, 0.2f, 0.3f, 1.0f });

        Kaydee::Renderer2D::drawQuad(
          { 0.5f, -0.5f }, { 0.5f, 0.75f }, 30.f, { 0.2f, 0.3f, 0.8f, 1.0f });

        Kaydee::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.01f },
                                     { 10.0f, 10.0f },
                                     0.0f,
                                     { 1.0f, 1.0f, 1.0f, 1.0f },
                                     checkerboardTexture);
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