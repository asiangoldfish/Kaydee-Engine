#ifndef __EXAMPLE_LAYER_H__
#define __EXAMPLE_LAYER_H__

#include <Kaydee/Kaydee.h>

class ExampleLayer : public Kaydee::Layer
{
public:
    ExampleLayer();
    void onUpdate(Kaydee::Timestep ts) override;
    void ExampleLayer::onEvent(Kaydee::Event& e) override;
    inline bool OnKeyPressedEvent(Kaydee::KeyPressedEvent& event)
    {
        return false;
    }
    virtual void onImGuiRender() override;

private:
    Kaydee::ShaderLibrary shaderLibrary;
    Kaydee::ref<Kaydee::Shader> shader;
    Kaydee::ref<Kaydee::VertexArray> vertexArray;

    Kaydee::ref<Kaydee::Shader> flatColorShader;
    Kaydee::ref<Kaydee::VertexArray> squareVA;

    Kaydee::ref<Kaydee::Texture2D> texture, pandaLogo;

    Kaydee::OrthographicCameraController cameraController;

    glm::vec3 squareColor = { 0.2f, 0.3f, 0.8f },
              checkerColor = { 1.0f, 1.0f, 1.0f },
              pandaColor = { 1.0f, 1.0f, 1.0f };
};

#endif // __EXAMPLE_LAYER_H__