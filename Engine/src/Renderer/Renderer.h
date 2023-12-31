#pragma once

#include "Renderer/RenderCommand.h"
#include "Renderer/RendererAPI.h"
#include <memory>
#include "Renderer/OrthographicCamera.h"
#include "Renderer/Shader.h"

namespace Kaydee {

    class Renderer
    {
    public:
        static void init();
        static void shutdown();
        static void onWindowResize(uint32_t width, uint32_t height);
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
