#ifndef __RENDERER_API_H__
#define __RENDERER_API_H__

#include <glm/glm.hpp>
#include "Renderer/VertexArray.h"

#include <memory>

namespace Kaydee {
    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL = 1
        };

    public:
        virtual void init() = 0;
        virtual void setViewport(uint32_t x,
                                 uint32_t y,
                                 uint32_t width,
                                 uint32_t height) = 0;
        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void clear() = 0;

        virtual void drawIndexed(const ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

        static inline API getAPI() { return api; }

    private:
        static API api;
    };
}

#endif // __RENDERER_API_H__