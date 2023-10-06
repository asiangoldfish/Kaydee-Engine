#include <Kaydee/Kaydee.h>
#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Kaydee::Application
{
public:
    Sandbox()
    {
        // pushLayer(new ExampleLayer());
        pushLayer(new Sandbox2D());
    }

    virtual ~Sandbox() {}
};

Kaydee::Application*
Kaydee::createApplication()
{
    return new Sandbox();
}