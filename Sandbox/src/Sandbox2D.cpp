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
        framebuffer->bind();
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
        framebuffer->unbind();
    }
}

void
Sandbox2D::onImGuiRender()
{
    // Set to true to enable dockspace
    static bool enableDockspace = true;
    if (enableDockspace) {
        // ImGui Dockspace
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static bool dockspaceOpen = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent
        // window not dockable into, because it would be confusing to have two
        // docking targets within each others.
        ImGuiWindowFlags window_flags =
          ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar |
                            ImGuiWindowFlags_NoCollapse |
                            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus |
                            ImGuiWindowFlags_NoNavFocus;
        } else {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will
        // render our background and handle the pass-thru hole, so we ask
        // Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka
        // window is collapsed). This is because we want to keep our DockSpace()
        // active. If a DockSpace() is inactive, all active windows docked into
        // it will lose their parent and become undocked. We cannot preserve the
        // docking relationship between an active window and an inactive
        // docking, otherwise any change of dockspace/settings would lead to
        // windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,
                                ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    dockspaceOpen = false;
                    Kaydee::Application::get().close();
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }
        ImGui::End();
    }

    ImGui::Begin("Statistics");
    auto stats = Kaydee::Renderer2D::getStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.drawCalls);
    ImGui::Text("Quads: %d", stats.quadCount);
    ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
    ImGui::Text("Indices: %d", stats.getTotalIndexCount());
    ImGui::End();

    ImGui::Begin("Viewport");
    static auto textureID = framebuffer->getColorAttachmentRendererID();
    ImGui::Image((void*)textureID,
                 ImVec2{ 1280.0f, 720.0f },
                 ImVec2{ 0, 1 },
                 ImVec2{ 1, 0 });
    ImGui::End();
}

void
Sandbox2D::onEvent(Kaydee::Event& e)
{
    cameraController.onEvent(e);
}