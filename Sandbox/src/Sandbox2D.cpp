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

    // Quad 2 properties
    quad2Props.position = { 0.0f, 0.0f, 0.0f };
    quad2Props.scale = { 0.3f, 0.3f, 1.0f };
    quad2Props.color = { 1.0f, 1.0f, 1.0f, 1.0f };

    // Particle properties
    particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
    particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
    particle.SizeBegin = 0.1f;
    particle.SizeVariation = 0.3f;
    particle.SizeEnd = 0.0f;
    particle.LifeTime = 1.0f;
    particle.Velocity = { 0.0f, 0.0f };
    particle.VelocityVariation = { 3.0f, 1.0f };
    particle.Position = { 0.0f, 0.0f };

    // Sprite sheet
    spriteSheet = Kaydee::Texture2D::create(
      GAME_ASSETS + std::string("textures/RPGpack_sheet_2X.png"));

    textureStairs = Kaydee::SubTexture2D::createFromCoords(
      spriteSheet, { 7, 6 }, { 128, 128 });
    textureBarrels = Kaydee::SubTexture2D::createFromCoords(
      spriteSheet, { 8, 2 }, { 128, 128 });
    textureTree = Kaydee::SubTexture2D::createFromCoords(
      spriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });

    Kaydee::FramebufferSpecification fbSpec;
    fbSpec.width = 1280;
    fbSpec.height = 720;
    framebuffer = Kaydee::Framebuffer::create(fbSpec);
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

#if 0
    {
        KD_PROFILE_SCOPE("Draw");
        Kaydee::Renderer2D::beginScene(cameraController.getCamera());

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

    {
        // Generate tiles
        KD_PROFILE_SCOPE("Draw Grid");
        Kaydee::Renderer2D::beginScene(cameraController.getCamera());

        int quads = 20;
        float gap = 1.1f;
        quad2Props.scale = { 1.0f, 1.0f, 1.0f };
        for (int y = 0; y < quads; y++) {
            quad2Props.position.y = y * gap;
            for (int x = 0; x < quads; x++) {
                quad2Props.position.x = x * gap;

                quad2Props.color.r = (float)x / quads;
                quad2Props.color.g = (float)y / quads;
                quad2Props.color.b =
                  1.0f - quad2Props.color.r - quad2Props.color.g;

                Kaydee::Renderer2D::drawQuad(&quad2Props);
            }
        }

        Kaydee::Renderer2D::endScene();
    }
#endif
    /*
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
        for (int i = 0; i < 5; i++) {
            particleSystem.Emit(particle);
        }
    }
    */

    particleSystem.OnRender(cameraController.getCamera());
    {
        // Generate tiles
        KD_PROFILE_SCOPE("Draw Spritesheet");
        Kaydee::Renderer2D::beginScene(cameraController.getCamera());

        Kaydee::Quad2DProperties quadProps;
        // quadProps.texture = spriteSheet;
        quadProps.subTexture = textureStairs;
        quadProps.position.z = 0.5f;
        Kaydee::Renderer2D::drawQuad(&quadProps);

        quadProps.subTexture = textureBarrels;
        quadProps.position.x = 1.0f;
        quadProps.position.z = 0.5f;
        Kaydee::Renderer2D::drawQuad(&quadProps);

        quadProps.subTexture = textureTree;
        quadProps.position.x = 2.0f;
        quadProps.position.z = 0.5f;
        quadProps.scale.y = 2;
        Kaydee::Renderer2D::drawQuad(&quadProps);

        Kaydee::Renderer2D::endScene();
    }
}

void
Sandbox2D::onImGuiRender()
{
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