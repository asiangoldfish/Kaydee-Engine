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
          const ref<VertexBuffer>& vertexBuffer) override;
        virtual void setIndexBuffer(
          const ref<IndexBuffer>& indexBuffer) override;

        virtual std::vector<Kaydee::ref<VertexBuffer>>& getVertexBuffers()
          override
        {
            return vertexBuffers;
        }

        virtual Kaydee::ref<IndexBuffer>& getIndexBuffer() override
        {
            return indexBuffer;
        }

    private:
        uint32_t rendererID;
        std::vector<Kaydee::ref<VertexBuffer>> vertexBuffers;
        ref<IndexBuffer> indexBuffer;
    };
}

#endif // __OPENGL_VERTEX_ARRAY_H__