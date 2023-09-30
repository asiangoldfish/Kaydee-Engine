#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Renderer/RenderCommand.h"
#include "Renderer/RendererAPI.h"
#include <memory>
#include "Renderer/OrthographicCamera.h"
#include "Renderer/Shader.h"

namespace Kaydee {

    class Renderer
    {
    public:
        static void beginScene(OrthographicCamera& camera);
        static void endScene();

        static void submit(const ref<Shader>& shader,
                           const ref<VertexArray>& VertexArray,
                           const glm::mat4& transform = glm::mat4(1.0f));

        static inline RendererAPI::API getAPI()
        {
            return RendererAPI::getAPI();
        }

    private:
        struct SceneData
        {
            glm::mat4 viewProjectionMatrix;
        };

        static SceneData* sceneData;
    };

}

#endif // __RENDERER_H__