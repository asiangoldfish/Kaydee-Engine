#include "ParticleSystem.h"

#include "Utils/rng.h"
#include <glad/glad.h>

#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>
#include <glm/gtc/type_ptr.hpp>

ParticleSystem::ParticleSystem(uint32_t maxParticles)
  : m_PoolIndex(maxParticles - 1)
{
    m_ParticlePool.resize(maxParticles);
}

void
ParticleSystem::OnUpdate(Kaydee::Timestep ts)
{
    for (auto& particle : m_ParticlePool) {
        if (!particle.Active)
            continue;

        if (particle.LifeRemaining <= 0.0f) {
            particle.Active = false;
            continue;
        }

        particle.LifeRemaining -= ts;
        particle.Position += particle.Velocity * (float)ts;
        particle.Rotation += 0.01f * ts;
    }
}

void
ParticleSystem::OnRender(Kaydee::OrthographicCamera& camera)
{
    Kaydee::Renderer2D::beginScene(camera);
    for (auto& particle : m_ParticlePool) {
        if (!particle.Active)
            continue;

        // Fade away particles
        float life = particle.LifeRemaining / particle.LifeTime;
        glm::vec4 color =
          glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
        // color.a = color.a * life;

        float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);

        Kaydee::Quad2DProperties quadProps;
        quadProps.position = { particle.Position.x, particle.Position.y, 1.0f };
        quadProps.scale = { size, size, 0.0f };
        quadProps.rotation = particle.Rotation;
        quadProps.color = color;

        Kaydee::Renderer2D::drawQuad(&quadProps);
    }
    Kaydee::Renderer2D::endScene();
}

void
ParticleSystem::Emit(const ParticleProps& particleProps)
{
    Particle& particle = m_ParticlePool[m_PoolIndex];
    particle.Active = true;
    particle.Position = particleProps.Position;
    particle.Rotation = Random::rng() * 2.0f * glm::pi<float>();

    // Velocity
    particle.Velocity = particleProps.Velocity;
    particle.Velocity.x +=
      particleProps.VelocityVariation.x * (Random::rng() - 0.5f);
    particle.Velocity.y +=
      particleProps.VelocityVariation.y * (Random::rng() - 0.5f);

    // Color
    particle.ColorBegin = particleProps.ColorBegin;
    particle.ColorEnd = particleProps.ColorEnd;

    particle.LifeTime = particleProps.LifeTime;
    particle.LifeRemaining = particleProps.LifeTime;
    particle.SizeBegin = particleProps.SizeBegin +
                         particleProps.SizeVariation * (Random::rng() - 0.5f);
    particle.SizeEnd = particleProps.SizeEnd;

    m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}