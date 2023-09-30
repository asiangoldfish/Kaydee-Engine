#include "kdpch.h"
#include "Renderer/Renderer.h"
#include "Renderer/RendererAPI.h"
#include "Renderer/RenderCommand.h"
#include "Platforms/OpenGL/OpenGLShader.h"
#include "Renderer.h"

namespace Kaydee {

    Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;

    void Renderer::init()
    {
        RenderCommand::init();
    }

    void Renderer::beginScene(OrthographicCamera& camera)
    {
        sceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
    }

    void Renderer::endScene() {}

    void Renderer::submit(const ref<Shader>& shader,
                          const ref<VertexArray>& vertexArray,
                          const glm::mat4& transform)
    {
        shader->bind();

        std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4(
          "u_viewProjection", sceneData->viewProjectionMatrix);

        std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4(
          "u_transform", transform);

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

}