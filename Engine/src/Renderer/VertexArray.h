#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

#include "Renderer/Buffer.h"
#include <memory>
#include <vector>

namespace Kaydee {
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void addVertexBuffer(
          const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;

        virtual void setIndexBuffer(
          const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

        virtual std::vector<std::shared_ptr<VertexBuffer>>&
        getVertexBuffers() = 0;

        virtual std::shared_ptr<IndexBuffer>& getIndexBuffer() = 0;

        static VertexArray* create();
    };
}

#endif // __VERTEX_ARRAY_H__