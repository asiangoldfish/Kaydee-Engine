#include "kdpch.h"
#include "Renderer/Texture.h"

#include "Renderer.h"
#include "Platforms/OpenGL/OpenGLTexture.h"

#include <memory>

namespace Kaydee {

    ref<Texture2D> Texture2D::create(const std::string& path)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                KD_CORE_ASSERT(false,
                               "RendererAPI::NONE is currently not supported!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return createRef<OpenGLTexture2D>(path);
        }

        KD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}