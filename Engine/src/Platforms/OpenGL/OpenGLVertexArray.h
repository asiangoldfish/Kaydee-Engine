#ifndef __OPENGL_VERTEX_ARRAY_H__
#define __OPENGL_VERTEX_ARRAY_H__

#include "Renderer/VertexArray.h"

namespace Kaydee {
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual void addVertexBuffer(
          const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void setIndexBuffer(
          const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        virtual std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers()
          override
        {
            return vertexBuffers;
        }

        virtual std::shared_ptr<IndexBuffer>& getIndexBuffer() override
        {
            return indexBuffer;
        }

    private:
        uint32_t rendererID;
        std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
        std::shared_ptr<IndexBuffer> indexBuffer;
    };
}

#endif // __OPENGL_VERTEX_ARRAY_H__