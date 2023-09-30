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
          const ref<VertexBuffer>& vertexBuffer) = 0;

        virtual void setIndexBuffer(
          const ref<IndexBuffer>& indexBuffer) = 0;

        virtual std::vector<ref<VertexBuffer>>&
        getVertexBuffers() = 0;

        virtual ref<IndexBuffer>& getIndexBuffer() = 0;

        static VertexArray* create();
    };
}

#endif // __VERTEX_ARRAY_H__