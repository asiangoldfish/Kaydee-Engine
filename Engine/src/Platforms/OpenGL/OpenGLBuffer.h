#pragma once

#include "Renderer/Buffer.h"

namespace Kaydee {
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(uint32_t size);
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer() override;

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual void setData(const void* data, uint32_t size) override;

        virtual const BufferLayout& getLayout() const { return layout; }

        virtual void setLayout(const BufferLayout& layout)
        {
            this->layout = layout;
        }

    private:
        uint32_t rendererID;
        BufferLayout layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer() override;

        void bind() const override;
        void unbind() const override;

        virtual uint32_t getCount() const override { return count; }

    private:
        uint32_t rendererID;
        uint32_t count;
    };
}
