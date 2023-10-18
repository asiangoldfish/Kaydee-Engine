#include "EditorLayer.h"

#include "Kaydee/Kaydee.h"
#include "imgui/imgui.h"
#include "Platforms/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

namespace Kaydee {
    static void ImGuiDocking() {
        // ------
        // BEGIN Dockspace
        // ------

        // Set to true to enable dockspace
        static bool enableDockspace = true;
        // ImGui Dockspace
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static bool dockspaceOpen = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the
        // parent window not dockable into, because it would be confusing to
        // have two docking targets within each others.
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

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace()
        // will render our background and handle the pass-thru hole, so we
        // ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false
        // (aka window is collapsed). This is because we want to keep our
        // DockSpace() active. If a DockSpace() is inactive, all active
        // windows docked into it will lose their parent and become
        // undocked. We cannot preserve the docking relationship between an
        // active window and an inactive docking, otherwise any change of
        // dockspace/settings would lead to windows being stuck in limbo and
        // never being visible.
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

        // ------
        // END Dockspace
        // ------
    }

    EditorLayer::EditorLayer()
      : Kaydee::Layer("EditorLayer")
      , cameraController(1280.0f / 720.0f, true)
    {
    }

    void EditorLayer::onAttach()
    {
        KD_PROFILE_FUNCTION();
        checkerboardTexture =
          Kaydee::Texture2D::create("assets/textures/checkerboard.png");

        // Quad 2 properties
        quad2Props.position = { 0.0f, 0.0f, 0.0f };
        quad2Props.scale = { 0.3f, 0.3f, 1.0f };
        quad2Props.color = { 1.0f, 1.0f, 1.0f, 1.0f };

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

    void EditorLayer::onDetach()
    {
        KD_PROFILE_FUNCTION();
    }

    void EditorLayer::onUpdate(Kaydee::Timestep ts)
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
        if (viewportFocused) {
            cameraController.onUpdate(ts);
        }

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

    void EditorLayer::onImGuiRender()
    {
        ImGuiDocking();

        ImGui::Begin("Statistics");
        auto stats = Kaydee::Renderer2D::getStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.drawCalls);
        ImGui::Text("Quads: %d", stats.quadCount);
        ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
        ImGui::Text("Indices: %d", stats.getTotalIndexCount());
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");

        if ((viewportFocused = ImGui::IsWindowFocused())) {
            Application::get().getImGuiLayer()->setBlockEvents(!viewportFocused);
        }

        cameraController.setEnableZooming(ImGui::IsWindowHovered()) ;

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

        // If ImGUI viewport's size changes, then we recreate the framebuffer.
        if (viewportSize != *((glm::vec2*)&viewportPanelSize)) {
            viewportSize = { viewportPanelSize.x, viewportPanelSize.y };

            cameraController.onResize(viewportPanelSize.x, viewportPanelSize.y);
        }

        static auto textureID = framebuffer->getColorAttachmentRendererID();
        ImGui::Image((void*)textureID,
                     ImVec2{ viewportSize.x, viewportSize.y },
                     ImVec2{ 0, 1 },
                     ImVec2{ 1, 0 });
        ImGui::End();
        ImGui::PopStyleVar();
    }

    void EditorLayer::onEvent(Kaydee::Event& e)
    {
        cameraController.onEvent(e);
    }
}