#ifndef __SANDBOX_2D_H__
#define __SANDBOX_2D_H__

#include "Kaydee/Kaydee.h"

/**
 * @brief 2D layer for Sandbox
 *
 */
class Sandbox2D : public Kaydee::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void onAttach() override;
    virtual void onDetach() override;
    void onUpdate(Kaydee::Timestep ts) override;
    virtual void onImGuiRender() override;
    void onEvent(Kaydee::Event& e) override;

private:
    Kaydee::OrthographicCameraController cameraController;

    // Temporary
    Kaydee::ref<Kaydee::VertexArray> squareVA;
    Kaydee::ref<Kaydee::Shader> flatColorShader;

    Kaydee::ref<Kaydee::Texture2D> checkerboardTexture;

    glm::vec4 squareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

#endif // __SANDBOX_2D_H__