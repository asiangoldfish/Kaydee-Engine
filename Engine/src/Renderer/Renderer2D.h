#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"
#include "SubTexture2D.h"
#include "Shader.h"

namespace Kaydee {

    struct Quad2DProperties
    {
        glm::vec3 position;
        glm::vec3 scale;
        float rotation = 0.0f;  ///< In degrees (not radians)
        glm::vec4 color;
        float tilingFactor = 1.0f;

        // If the quad renders a texture, then we display the whole texture.
        // Else, if the quad renders a quad texture, we make sure to account
        // for this. Only one of texture or subTexture can be in use, and not
        // both at one time. If both is nullptr, then no texture is rendered.
        ref<Texture2D> texture;
        ref<SubTexture2D> subTexture;

        Quad2DProperties()
          : position(0.0f)
          , scale(1.0f)
          , color(1.0f)
          , texture(nullptr)
        {
        }
    };

    class Renderer2D
    {
    public:
        static void init();
        static void shutdown();

        static void beginScene(const OrthographicCamera& camera);
        static void endScene();

        static void flush();

        // Primitives. Rotation is in radians.
        static void drawQuad(const Quad2DProperties* properties);
        static ref<Shader>& getShader();

        struct Statistics
        {
            uint32_t drawCalls = 0, quadCount = 0;
            uint32_t getTotalVertexCount() { return quadCount * 4; }
            uint32_t getTotalIndexCount() { return quadCount * 6; }
        };
        static void resetStats();
        static Statistics getStats();

    private:
        static void flushAndReset();
    };
}
