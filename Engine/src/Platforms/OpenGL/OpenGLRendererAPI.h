#ifndef __OPENGL_RENDERER_API_H__
#define __OPENGL_RENDERER_API_H__

#include "Renderer/RendererAPI.h"

namespace Kaydee {
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void setClearColor(const glm::vec4& color) override;
        virtual void clear() override;

        virtual void drawIndexed(
          const std::shared_ptr<VertexArray>& vertexArray) override;
    };
}

#endif