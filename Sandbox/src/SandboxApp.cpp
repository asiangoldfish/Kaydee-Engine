#include <Kaydee/Kaydee.h>

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
    }

    void onEvent(Kaydee::Event& event) override
    {
        // KD_TRACE("{0}", event);
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