#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "Renderer/Renderer.h"

namespace Kaydee {
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static VertexBuffer* create(float* vertices, uint32_t size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getCount() const = 0;

        static IndexBuffer* create(uint32_t* indices, uint32_t size);
    };
}

#endif // __BUFFER_H__