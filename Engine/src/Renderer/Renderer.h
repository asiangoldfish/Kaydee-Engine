#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Renderer/RenderCommand.h"
#include "Renderer/RendererAPI.h"
#include <memory>

namespace Kaydee {
    class Renderer
    {
    public:
        static void beginScene();
        static void endScene();

        static void submit(const std::shared_ptr<VertexArray>& VertexArray);

        static inline RendererAPI::API getAPI()
        {
            return RendererAPI::getAPI();
        }
    };
}

#endif // __RENDERER_H__