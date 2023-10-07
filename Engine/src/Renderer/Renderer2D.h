#ifndef __RENDER_2D_H__
#define __RENDER_2D_H__

#include "OrthographicCamera.h"
#include "Texture.h"
#include "Shader.h"

namespace Kaydee {

    struct Quad2DProperties
    {
        glm::vec3 position;
        glm::vec3 size;
        float rotation = 0.0f;  ///< In degrees (not radians)
        glm::vec4 color;
        float tilingFactor = 1.0f;
        ref<Texture2D> texture;

        Quad2DProperties()
          : position(0.0f)
          , size(1.0f)
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

        // Primitives
        static void drawQuad(const Quad2DProperties* properties);

        static ref<Shader>& getShader();
    };
}

#endif // __RENDER_2D_H__