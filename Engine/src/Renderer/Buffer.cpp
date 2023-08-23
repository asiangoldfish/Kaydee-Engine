#include "kdpch.h"

#include "Renderer/Buffer.h"
#include "Renderer/Renderer.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"

namespace Kaydee {
    VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::NONE:
                KD_CORE_ASSERT(false,
                               "RendererAPI::NONE is currently not supported!");
                return nullptr;

            case RendererAPI::OPENGL:
                return new OpenGLVertexBuffer(vertices, size);
        }

        KD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::NONE:
                KD_CORE_ASSERT(false,
                               "RendererAPI::NONE is currently not supported!");
                return nullptr;

            case RendererAPI::OPENGL:
                return new OpenGLIndexBuffer(indices, size);
        }

        KD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}