#include "kdpch.h"
#include "Shader.h"

#include "Renderer/Renderer.h"
#include "Platforms/OpenGL/OpenGLShader.h"

namespace Kaydee {
    Shader* Shader::create(const std::string& filepath)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                KD_CORE_ASSERT(false,
                               "RendererAPI::NONE is currently not supported!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return new OpenGLShader(filepath);
        }

        KD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Shader* Shader::create(const std::string& vertexSrc,
                           const std::string& fragmentSrc)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                KD_CORE_ASSERT(false,
                               "RendererAPI::NONE is currently not supported!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        KD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}