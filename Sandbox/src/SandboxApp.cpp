#include <Kaydee/Kaydee.h>

class Sandbox : public Kaydee::Application
{
public:
    Sandbox()
    {

    }

    virtual ~Sandbox()
    {

    }
};

Kaydee::Application* Kaydee::createApplication()
{
    return new Sandbox();
}