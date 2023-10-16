#include "kdpch.h"
#include "Framebuffer.h"

#include "Renderer/Renderer.h"
#include "Platforms/OpenGL/OpenGLFramebuffer.h"

namespace Kaydee {
    ref<Framebuffer> Framebuffer::create(const FramebufferSpecification& spec)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                KD_CORE_ASSERT(false,
                               "RendererAPI::NONE is currently not supported!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return createRef<OpenGLFramebuffer>(spec);
        }

        KD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}