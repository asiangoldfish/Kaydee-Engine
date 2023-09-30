#ifndef __OPENGL_RENDERER_API_H__
#define __OPENGL_RENDERER_API_H__

#include "Renderer/RendererAPI.h"

namespace Kaydee {
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void init() override;
        virtual void setClearColor(const glm::vec4& color) override;
        virtual void clear() override;

        virtual void drawIndexed(
          const ref<VertexArray>& vertexArray) override;
    };
}

#endif