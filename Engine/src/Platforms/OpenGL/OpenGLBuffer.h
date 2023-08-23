#ifndef __OPENGL_BUFFER_H__
#define __OPENGL_BUFFER_H__

#include "Renderer/Buffer.h"

namespace Kaydee {
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer() override;

        void bind() const override;
        void unbind() const override;

    private:
        uint32_t rendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer() override;

        void bind() const override;
        void unbind() const override;

        uint32_t getCount() const override { return count; }

    private:
        uint32_t rendererID;
        uint32_t count;
    };
}

#endif // __OPENGL_BUFFER_H__