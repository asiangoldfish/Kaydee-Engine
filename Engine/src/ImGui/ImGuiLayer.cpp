#include "ImGui/ImGuiLayer.h"
#include "Core/Application.h"
#include "Core/Core.h"
#include "Events/Event.h"
#include "Platforms/OpenGL/ImGuiOpenGLRenderer.h"
#include "kdpch.h"
#include <imgui.h>

// TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Kaydee {
    ImGuiLayer::ImGuiLayer()
      : Layer("ImGuiLayer")
    {
        time = 0.f;
    }

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::onAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // TODO - Replace with Kaydee Keycodes
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }
    void ImGuiLayer::onDetach() {}
    void ImGuiLayer::onUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::get();

        io.DisplaySize = ImVec2((float)app.getWindow().getWidth(),
                                (float)app.getWindow().getHeight());

        float gTime = (float)glfwGetTime();
        io.DeltaTime = gTime > 0.0f ? (gTime - time) : (1.0f / 60.0f);
        time = gTime;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        // Mouse release
        dispatcher.dispatch<MouseButtonPressedEvent>(
          KD_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));

        // Mouse press
        dispatcher.dispatch<MouseButtonReleasedEvent>(
          KD_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));

        // Mouse move
        dispatcher.dispatch<MouseMovedEvent>(
          KD_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));

        // Mouse scroll
        dispatcher.dispatch<MouseScrolledEvent>(
          KD_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));

        // Key press
        dispatcher.dispatch<KeyPressedEvent>(
          KD_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));

        // Key release
        dispatcher.dispatch<KeyReleasedEvent>(
          KD_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));

        // Key type
        dispatcher.dispatch<KeyTypedEvent>(
          KD_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));

        // Window resize
        dispatcher.dispatch<WindowResizeEvent>(
          KD_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
    }

    void ImGuiLayer::begin() {}
    void ImGuiLayer::end() {}

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.getMouseButton()] = true;
        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.getMouseButton()] = false;
        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.getX(), e.getY());
        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.getOffsetX();
        io.MouseWheel += e.getOffsetY();
        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.getKeyCode()] = true;

        // Detect modifier keys
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] ||
                     io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift =
          io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt =
          io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper =
          io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.getKeyCode()] = false;
        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        int keyCode = e.getKeyCode();
        if (keyCode > 0 && keyCode < 0x10000) {
            io.AddInputCharacter((unsigned short)keyCode);
        }
        return false;
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)e.getWidth(), (float)e.getHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, e.getWidth(), e.getHeight());
        return false;
    }
}