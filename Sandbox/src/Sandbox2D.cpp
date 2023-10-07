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

    // Chessboard properties
    chessProps.position.z = -0.1f;
    chessProps.size = { 10.0f, 10.0f, 1.0f };
    chessProps.color = { 1.0f, 1.0f, 1.0f, 1.0f };
    chessProps.texture = checkerboardTexture;
    chessProps.tilingFactor = 1.0f;

    // Quad 1 properties
    quad1Props.position.x = -1;
    quad1Props.size = { 0.8f, 0.8f, 1.0f };
    quad1Props.color = { .8f, 0.2f, 0.3f, 0.9f };

    // Quad 2 properties
    quad2Props.position = { 0.5f, -0.5f, 0.0f };
    quad2Props.size = { 0.5f, 0.75f, 1.0f };
    quad2Props.rotation = glm::radians(30.f);
    quad2Props.color = { 0.2f, 0.3f, 0.8f, 1.0f };
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
    elapsedTime += ts.getMilliseconds() * quad1Pos;

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
        Kaydee::ref<Kaydee::Shader> shader = Kaydee::Renderer2D::getShader();

        KD_PROFILE_SCOPE("Draw");
        Kaydee::Renderer2D::beginScene(cameraController.getCamera());

        chessProps.rotation = glm::radians(chessRotation);
        Kaydee::Renderer2D::drawQuad(&chessProps);

        float radians = glm::radians(elapsedTime);
        quad1Props.position.x = cos(radians) * quad1Radius;
        quad1Props.position.y = sin(radians) * quad1Radius;
        quad1Props.rotation = glm::radians(quad1LocalRotation);
        Kaydee::Renderer2D::drawQuad(&quad1Props);

        Kaydee::Renderer2D::drawQuad(&quad2Props);

        Kaydee::Renderer2D::endScene();
    }
}

void
Sandbox2D::onImGuiRender()
{
    ImGui::Begin("Settings");

    ImGui::Text("FPS: %d", fps);
    ImGui::SliderFloat("Checker Tiling", &chessProps.tilingFactor, 1, 20);
    ImGui::SliderFloat("Chess Rotate", &chessRotation, 0.0f, 360.0f);
    ImGui::NewLine();
    ImGui::SliderFloat("Quad1 Rotation Speed", &quad1Pos, 0.0f, 1.0f);
    ImGui::SliderFloat("Quad1 Radius", &quad1Radius, 0.0f, 10.f);
    ImGui::SliderFloat("Quad1 Local Rotation", &quad1LocalRotation, 0.0f, 360.f);

    ImGui::End();
}

void
Sandbox2D::onEvent(Kaydee::Event& e)
{
    cameraController.onEvent(e);
}