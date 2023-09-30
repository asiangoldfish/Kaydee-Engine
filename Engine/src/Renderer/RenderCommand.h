#ifndef __RENDER_COMMAND_H__
#define __RENDER_COMMAND_H__

#include "Renderer/VertexArray.h"
#include "Renderer/RendererAPI.h"
#include <memory>

namespace Kaydee {
    class RenderCommand
    {
    public:
        inline static void init() { rendererAPI->init(); }

        inline static void setClearColor(const glm::vec4& color)
        {
            rendererAPI->setClearColor(color);
        }

        inline static void clear() { rendererAPI->clear(); }

        inline static void drawIndexed(const ref<VertexArray>& vertexArray)
        {
            rendererAPI->drawIndexed(vertexArray);
        }

    private:
        static RendererAPI* rendererAPI;
    };
}

#endif // __RENDER_COMMAND_H__