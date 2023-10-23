#include "EditorLayer.h"

#include "Kaydee/Kaydee.h"
#include "imgui/imgui.h"
#include "Platforms/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

namespace Kaydee {
    static void ImGuiDocking()
    {
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
                    Application::get().close();
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
      : Layer("EditorLayer")
      , cameraController(1280.0f / 720.0f, true)
    {
    }

    void EditorLayer::onAttach()
    {
        KD_PROFILE_FUNCTION();

        FramebufferSpecification fbSpec;
        fbSpec.width = 1280;
        fbSpec.height = 720;
        framebuffer = Framebuffer::create(fbSpec);

        // --------
        // Scene and entities
        // --------
        activeScene = createRef<Scene>();

        Entity square = activeScene->createEntity("Green Square");
        square.addComponent<SpriteRendererComponent>(
          glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        squareEntity = square;
        
        auto redSquare = activeScene->createEntity("Red Square");
        redSquare.addComponent<SpriteRendererComponent>(glm::vec4({1.0f, 0.0f, 0.0f, 1.0f}));

        firstCameraEntity = activeScene->createEntity("First Camera Entity");
        auto& camera = firstCameraEntity.addComponent<CameraComponent>();
        camera.fixedAspectRatio = false;

        class CameraController : public ScriptableEntity
        {
        public:
            void onCreate() {}

            void onUpdate(Timestep ts)
            {
                auto& transform = getComponent<TransformComponent>().transform;
                float speed = 5.0f;

                if (Input::isKeyPressed(KD_KEY_A)) {
                    transform[3][0] -= speed * ts;
                }
                if (Input::isKeyPressed(KD_KEY_D)) {
                    transform[3][0] += speed * ts;
                }
                if (Input::isKeyPressed(KD_KEY_W)) {
                    transform[3][1] += speed * ts;
                }
                if (Input::isKeyPressed(KD_KEY_S)) {
                    transform[3][1] -= speed * ts;
                }
            }

            void onDestroy() {}
        };
        secondCameraEntity = activeScene->createEntity("Second camera entity");
        secondCameraEntity.addComponent<CameraComponent>();
        firstCameraEntity.addComponent<NativeScriptComponent>()
          .bind<CameraController>();

        sceneHierarchyPanel.setContext(activeScene);
    }

    void EditorLayer::onDetach()
    {
        KD_PROFILE_FUNCTION();
    }

    void EditorLayer::onUpdate(Timestep ts)
    {
        KD_PROFILE_FUNCTION();

        //------------
        // Update

        // activeScene->onViewportResize((uint32_t)viewportSize.x,
        // viewportSize.y);
        //  Camera
        if (viewportFocused) {
            cameraController.onUpdate(ts);
        }

        //------------
        // Render
        //------------
        // Reset stats
        Renderer2D::resetStats();
        {
            framebuffer->bind();
            RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            RenderCommand::clear();
        }

        // Scene
        Renderer2D::beginScene(cameraController.getCamera());

        // Update current scene
        activeScene->onUpdate(ts);

        Renderer2D::endScene();

        framebuffer->unbind();
    }

    void EditorLayer::onImGuiRender()
    {
        ImGuiDocking();

        sceneHierarchyPanel.onImGuiRender();

        // ----------
        // Statistics
        // ----------
        ImGui::Begin("Statistics");
        {
            auto stats = Renderer2D::getStats();
            ImGui::Text("Renderer2D Stats:");
            ImGui::Text("Draw Calls: %d", stats.drawCalls);
            ImGui::Text("Quads: %d", stats.quadCount);
            ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
            ImGui::Text("Indices: %d", stats.getTotalIndexCount());

            if (squareEntity) {
                ImGui::Separator();
                ImGui::Text(
                  "%s", squareEntity.getComponent<TagComponent>().tag.c_str());
                auto& squareColor =
                  squareEntity.getComponent<SpriteRendererComponent>().color;

                ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
                ImGui::Separator();
            }
            ImGui::End();

            ImGui::Begin("Inspector");
            {
                auto& camera =
                  firstCameraEntity.getComponent<CameraComponent>().camera;
                float orthoSize = camera.getOrthographicSize();
                if (ImGui::DragFloat("Camera Ortho Size", &orthoSize)) {
                    camera.setOrthographicSize(orthoSize);
                }

                glm::mat4& cameraTransform =
                  firstCameraEntity.getComponent<TransformComponent>()
                    .transform;
                ImGui::DragFloat3("Camera Transform",
                                  glm::value_ptr(cameraTransform[3]));
            }
        }
        ImGui::End();

        // ----------
        // Viewport
        // ----------
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");
        {
            if ((viewportFocused = ImGui::IsWindowFocused())) {
                Application::get().getImGuiLayer()->setBlockEvents(
                  !viewportFocused);
            }

            cameraController.setEnableZooming(ImGui::IsWindowHovered());

            ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

            // If ImGUI viewport's size changes, then we recreate the
            // framebuffer.
            if (viewportSize != *((glm::vec2*)&viewportPanelSize)) {
                viewportSize = { viewportPanelSize.x, viewportPanelSize.y };
                cameraController.onResize(viewportPanelSize.x,
                                          viewportPanelSize.y);
                activeScene->onViewportResize((uint32_t)viewportSize.x,
                                              (uint32_t)viewportSize.y);
            }

            static auto textureID = framebuffer->getColorAttachmentRendererID();
            ImGui::Image((void*)textureID,
                         ImVec2{ viewportSize.x, viewportSize.y },
                         ImVec2{ 0, 1 },
                         ImVec2{ 1, 0 });
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }

    void EditorLayer::onEvent(Event& e)
    {
        cameraController.onEvent(e);
    }
}