#ifndef __RENDER_2D_H__
#define __RENDER_2D_H__

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Kaydee {

    class Renderer2D
    {
    public:
        static void init();
        static void shutdown();

        static void beginScene(const OrthographicCamera& camera);
        static void endScene();

        // Primitives
        static void drawQuad(const glm::vec2& position,
                             const glm::vec2& size,
                             const float rotation,
                             const glm::vec4& color);

        static void drawQuad(const glm::vec3& position,
                             const glm::vec2& size,
                             const float rotation,
                             const glm::vec4& color);

        static void drawQuad(const glm::vec2& position,
                             const glm::vec2& size,
                             const float rotation,
                             const glm::vec4& color,
                             const ref<Texture2D> texture);

        static void drawQuad(const glm::vec3& position,
                             const glm::vec2& size,
                             const float rotation,
                             const glm::vec4& color,
                             const ref<Texture2D> texture);
    };
}

#endif // __RENDER_2D_H__