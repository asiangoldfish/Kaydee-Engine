#include <Kaydee/Kaydee.h>
#include <imgui/imgui.h>

class ExampleLayer : public Kaydee::Layer
{
public:
    ExampleLayer()
      : Layer("Example")
    {
    }

    void onUpdate() override
    {
        // KD_INFO("ExampleLayer::Update");
        if (Kaydee::Input::isKeyPressed(KD_KEY_TAB)) {
            KD_TRACE("Tab key is pressed (poll)!");
        }
    }

    void onEvent(Kaydee::Event& event) override
    {
        // KD_TRACE("{0}", event);
    }

    virtual void onImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello World");
        ImGui::End();
    }
};

class Sandbox : public Kaydee::Application
{
public:
    Sandbox() { pushLayer(new ExampleLayer()); }

    virtual ~Sandbox() {}
};

Kaydee::Application*
Kaydee::createApplication()
{
    return new Sandbox();
}