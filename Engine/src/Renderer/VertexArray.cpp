#include "VertexArray.h"

#include "kdpch.h"
#include "Renderer/Renderer.h"
#include "Renderer/RendererAPI.h"

#include "Platforms/OpenGL/OpenGLVertexArray.h"

namespace Kaydee {
    ref<VertexArray> VertexArray::create()
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                KD_CORE_ASSERT(false,
                               "RendererAPI::NONE is currently not supported!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLVertexArray>();
        }

        KD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}