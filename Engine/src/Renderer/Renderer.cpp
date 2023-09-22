#include "kdpch.h"
#include "Renderer/Renderer.h"
#include "Renderer/RendererAPI.h"
#include "Renderer/RenderCommand.h"

namespace Kaydee {
    void Renderer::beginScene() {}

    void Renderer::endScene() {}

    void Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        // Submit into render command queue
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

}