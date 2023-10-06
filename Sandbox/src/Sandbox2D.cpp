#include "Sandbox2D.h"

#include "Kaydee/Kaydee.h"
#include "imgui/imgui.h"
#include "Platforms/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

Sandbox2D::Sandbox2D()
  : Kaydee::Layer("Sandbox2D")
  , cameraController(1280.0f / 720.0f, true)
{
}

void
Sandbox2D::onAttach()
{
    KD_PROFILE_FUNCTION();

    checkerboardTexture =
      Kaydee::Texture2D::create("assets/textures/checkerboard.png");
}

void
Sandbox2D::onDetach()
{
    KD_PROFILE_FUNCTION();
}

void
Sandbox2D::onUpdate(Kaydee::Timestep ts)
{
    KD_PROFILE_FUNCTION();

    fps = 1000 / (int)ts.getMilliseconds();

    //------------
    // Update
    //------------
    cameraController.onUpdate(ts);

    //------------
    // Render
    //------------
    {
        KD_PROFILE_SCOPE("Render Prep");
        Kaydee::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Kaydee::RenderCommand::clear();
    }

    {
        int defaultTiling = 1;
        Kaydee::ref<Kaydee::Shader> shader = Kaydee::Renderer2D::getShader();

        KD_PROFILE_SCOPE("Draw");
        Kaydee::Renderer2D::beginScene(cameraController.getCamera());
        
        shader->setInt("u_tiling", tiling);
        Kaydee::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f },
                                     { 10.0f, 10.0f },
                                     0.0f,
                                     { 1.0f, 1.0f, 1.0f, 1.0f },
                                     checkerboardTexture);
        
        shader->setInt("u_tiling", defaultTiling);
        Kaydee::Renderer2D::drawQuad(
          { -1.0f, 0.0f }, { .8f, .8f }, 0.0f, { .8f, 0.2f, 0.3f, 0.9f });

        Kaydee::Renderer2D::drawQuad(
          { 0.5f, -0.5f }, { 0.5f, 0.75f }, 30.f, { 0.2f, 0.3f, 0.8f, 1.0f });
        Kaydee::Renderer2D::endScene();
    }
}

void
Sandbox2D::onImGuiRender()
{
    ImGui::Begin("Settings");

    ImGui::Text("FPS: %d", fps);
    ImGui::SliderInt("Tiling", &tiling, 1, 20, std::to_string(tiling).c_str());

    ImGui::End();
}

void
Sandbox2D::onEvent(Kaydee::Event& e)
{
    cameraController.onEvent(e);
}