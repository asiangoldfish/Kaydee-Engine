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
    chessProps.position = { -5.f, -5.f, -0.1f };
    chessProps.scale = { 10.0f, 10.0f, 1.0f };
    chessProps.color = { 1.0f, 1.0f, 1.0f, 0.4f };
    chessProps.texture = checkerboardTexture;
    chessProps.tilingFactor = 0.5f;

    // Chess 2
    chessProps2.position = { 0.5f, -0.5f, -0.1f };
    chessProps2.scale = { 1.0f, 1.0f, 1.0f };
    chessProps2.color = { 1.0f, 1.0f, 1.0f, 1.0f };
    chessProps2.texture = checkerboardTexture;
    chessProps2.tilingFactor = 20.0f;

    // Quad 1 properties
    quad1Props.position.x = -1;
    quad1Props.scale = { 0.8f, 0.8f, 1.0f };
    quad1Props.color = { .3f, 0.2f, 0.3f, 0.9f };

    // Quad 2 properties
    quad2Props.position = { 0.0f, 0.0f, 0.0f };
    quad2Props.scale = { 0.3f, 0.3f, 1.0f };
    quad2Props.color = { 1.0f, 1.0f, 1.0f, 1.0f };

    // Particle properties
    particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
    particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
    particle.SizeBegin = 0.5f;
    particle.SizeVariation = 0.3f;
    particle.SizeEnd = 0.0f;
    particle.LifeTime = 1.0f;
    particle.Velocity = { 0.0f, 0.0f };
    particle.VelocityVariation = { 3.0f, 1.0f };
    particle.Position = { 0.0f, 0.0f };
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
    timestep = ts.getMilliseconds();
    fps = (int)ts.getMilliseconds() ? 1000 / (int)ts.getMilliseconds() : 0;
    float iterationX = ts.getMilliseconds() * 0.01f * quad1Pos * quad1PosX;
    float iterationY = ts.getMilliseconds() * 0.01f * quad1Pos * quad1PosY;
    elapsedTimeX += iterationX;
    elapsedTimeY += iterationY;

    elapsedTimeColor += ts.getMilliseconds() * 0.01f * colorSpeed * 0.1f;

    //------------
    // Update
    //------------
    cameraController.onUpdate(ts);
    particleSystem.OnUpdate(ts);

    //------------
    // Render
    //------------
    // Reset stats
    Kaydee::Renderer2D::resetStats();
    {
        KD_PROFILE_SCOPE("Render Prep");
        Kaydee::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Kaydee::RenderCommand::clear();
    }

    {
        Kaydee::ref<Kaydee::Shader> shader = Kaydee::Renderer2D::getShader();

        KD_PROFILE_SCOPE("Draw");
        Kaydee::Renderer2D::beginScene(cameraController.getCamera());
        // Kaydee::Renderer2D::drawQuad(&chessProps2);
        // Kaydee::Renderer2D::drawQuad(&chessProps);
        // Kaydee::Renderer2D::drawQuad(&quad1Props);

        float tmpX = elapsedTimeX;
        float tmpY = elapsedTimeY;

        quad2Props.color.r = (1 + cos(elapsedTimeColor)) * 0.5f;
        quad2Props.color.g = (1 + sin(elapsedTimeColor)) * 0.5f;
        quad2Props.color.b = (1 + cos(sin(elapsedTimeColor))) * 0.5f;

        for (int i = 0; i < trailingQuads; i++) {
            quad2Props.position.x = cos(tmpX) * quad1Radius;
            quad2Props.position.y = sin(tmpY) * quad1Radius;
            quad2Props.color.a = trailingQuads * (trailingQuads - i);

            Kaydee::Renderer2D::drawQuad(&quad2Props);
            tmpX -= iterationX + quadDistance;
            tmpY -= iterationY + quadDistance;
        }

        Kaydee::Renderer2D::endScene();
    }

    // Emit particles
    if (Kaydee::Input::isMouseButtonPressed(KD_MOUSE_BUTTON_LEFT)) {
        auto [x, y] = Kaydee::Input::getMousePosition();
        auto width = Kaydee::Application::get().getWindow().getWidth();
        auto height = Kaydee::Application::get().getWindow().getHeight();

        auto bounds = cameraController.getBounds();
        auto pos = cameraController.getCamera().getPosition();
        x = (x / width) * bounds.getWidth() - bounds.getWidth() * 0.5f;
        y = bounds.getHeight() * 0.5f - (y / height) * bounds.getHeight();
        particle.Position = { x + pos.x, y + pos.y };
        for (int i = 0; i < 50; i++) {
            particleSystem.Emit(particle);
        }
    }

    particleSystem.OnRender(cameraController.getCamera());
}

void
Sandbox2D::onImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::Text("Frame-time: %.3fms (%d)", timestep, fps);
    ImGui::Text("Colors: %f %f %f %f",
                quad2Props.color.r,
                quad2Props.color.g,
                quad2Props.color.b,
                quad2Props.color.a);
    ImGui::InputInt("Quads Input", &trailingQuads, 1000, 100);
    ImGui::SliderInt("Quads", &trailingQuads, 0, 10000);
    ImGui::SliderFloat("Radius", &quad1Radius, 0, 10);
    ImGui::SliderFloat("Speed", &quad1Pos, 0, 1);
    ImGui::SliderFloat("SpeedX", &quad1PosX, 0, 3);
    ImGui::SliderFloat("SpeedY", &quad1PosY, 0, 3);
    ImGui::SliderFloat("Quad Distance", &quadDistance, 0, 1);
    ImGui::SliderFloat("Color Speed", &colorSpeed, 0, 3);
    ImGui::End();

    ImGui::Begin("Statistics");
    auto stats = Kaydee::Renderer2D::getStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.drawCalls);
    ImGui::Text("Quads: %d", stats.quadCount);
    ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
    ImGui::Text("Indices: %d", stats.getTotalIndexCount());
    ImGui::End();
}

void
Sandbox2D::onEvent(Kaydee::Event& e)
{
    cameraController.onEvent(e);
}