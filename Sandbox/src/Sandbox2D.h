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
    Kaydee::ref<Kaydee::Texture2D> checkerboardTexture;
    int fps = 0;

    Kaydee::Quad2DProperties chessProps, quad1Props, quad2Props;
    float chessRotation = 0.0f;
    float quad1Pos = 1.0f;
    float quad1Radius = 1.0f;
    float quad1LocalRotation = 0.0f;

    float elapsedTime = 0.0f;

};

#endif // __SANDBOX_2D_H__ vcb