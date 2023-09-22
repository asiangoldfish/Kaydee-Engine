#include "VertexArray.h"

#include "kdpch.h"
#include "Renderer/Renderer.h"

#include "Platforms/OpenGL/OpenGLVertexArray.h"

namespace Kaydee {
    VertexArray* VertexArray::create()
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::NONE:
                KD_CORE_ASSERT(false,
                               "RendererAPI::NONE is currently not supported!");
                return nullptr;

            case RendererAPI::OPENGL:
                return new OpenGLVertexArray();
        }

        KD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}