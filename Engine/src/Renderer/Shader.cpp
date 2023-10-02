#include "kdpch.h"
#include "Shader.h"

#include "Renderer/Renderer.h"
#include "Platforms/OpenGL/OpenGLShader.h"

namespace Kaydee {
    ref<Shader> Shader::create(const std::string& filepath)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                KD_CORE_ASSERT(false,
                               "RendererAPI::NONE is currently not supported!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return createRef<OpenGLShader>(filepath);
        }

        KD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    ref<Shader> Shader::create(const std::string& name,
                               const std::string& vertexSrc,
                               const std::string& fragmentSrc)
    {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:
                KD_CORE_ASSERT(false,
                               "RendererAPI::NONE is currently not supported!");
                return nullptr;

            case RendererAPI::API::OpenGL:
                return createRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        KD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    void ShaderLibrary::add(const std::string& name, const ref<Shader>& shader)
    {
        KD_CORE_ASSERT(!shaderExists(name),
                       "Shader" + name + "already exists!");
        shaders[name] = shader;
    }

    void ShaderLibrary::add(const ref<Shader>& shader)
    {
        auto& name = shader->getName();
        add(name, shader);
    }

    ref<Shader> ShaderLibrary::load(const std::string& filepath)
    {
        auto shader = Shader::create(filepath);
        add(shader);
        return shader;
    }

    ref<Shader> ShaderLibrary::load(const std::string& name,
                                    const std::string& filepath)
    {
        return ref<Shader>();
    }

    ref<Shader> ShaderLibrary::get(const std::string& name)
    {
        KD_CORE_ASSERT(shaderExists(name),
                       "Shader \'" + name + "\' does not exist!");
        return shaders[name];
    }

    bool ShaderLibrary::shaderExists(const std::string& name) const
    {
        return shaders.find(name) != shaders.end();
    }
}