#include "ImGui/ImGuiLayer.h"
#include "kdpch.h"

namespace Kaydee {
    ImGuiLayer::ImGuiLayer()
      : Layer("ImGuiLayer")
    {
    }
    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::onAttach() {}
    void ImGuiLayer::onDetach() {}
    void ImGuiLayer::onUpdate() {}
    void ImGuiLayer::onEvent(Event& e) {}
    void ImGuiLayer::begin() {}
    void ImGuiLayer::end() {}
}