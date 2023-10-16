#ifndef __SANDBOX_2D_H__
#define __SANDBOX_2D_H__

#include "Kaydee/Kaydee.h"
#include "ParticleSystem.h"

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
    Kaydee::ref<Kaydee::Texture2D> spriteSheet;
    Kaydee::ref<Kaydee::SubTexture2D> textureStairs;
    Kaydee::ref<Kaydee::SubTexture2D> textureBarrels;
    Kaydee::ref<Kaydee::SubTexture2D> textureTree;

    Kaydee::ref<Kaydee::Framebuffer> framebuffer;
    
    int fps = 0;

    Kaydee::Quad2DProperties quad2Props;
    float chessRotation = 0.0f;
    float quad1Pos = 1.0f;
    float quad1PosX = 1.0f;
    float quad1PosY = 1.0f;
    float quad1Radius = 1.0f;
    float quad1LocalRotation = 0.0f;
    int trailingQuads = 5;
    float quadDistance = 0.f;

    float colorSpeed = 0.5f;

    float elapsedTimeX = 0.0f;
    float elapsedTimeY = 0.0f;
    float elapsedTimeColor = 0.0f;
    float timestep = 0.0f;

    ParticleProps particle;
    ParticleSystem particleSystem;
};

#endif // __SANDBOX_2D_H__ vcb