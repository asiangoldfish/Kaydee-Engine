#include "kdpch.h"

#include "Renderer/Buffer.h"
#include "Renderer/Renderer.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"
#include "Renderer/RendererAPI.h"

namespace Kaydee {
    ref<VertexBuffer> VertexBuffer::create(uint32_t size)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                KD_CORE_ASSERT(false,
                               "RendererAPI::NONE is currently not supported!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return createRef<OpenGLVertexBuffer>(size);
        }

        KD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                KD_CORE_ASSERT(false,
                               "RendererAPI::NONE is currently not supported!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return createRef<OpenGLVertexBuffer>(vertices, size);
        }

        KD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                KD_CORE_ASSERT(false,
                               "RendererAPI::NONE is currently not supported!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return createRef<OpenGLIndexBuffer>(indices, size);
        }

        KD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}