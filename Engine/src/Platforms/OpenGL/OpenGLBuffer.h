#ifndef __OPENGL_BUFFER_H__
#define __OPENGL_BUFFER_H__

#include "Renderer/Buffer.h"

namespace Kaydee {
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        OpenGLVertexBuffer(uint32_t size);
        ~OpenGLVertexBuffer() override;

        void bind() const override;
        void unbind() const override;

    private:
        uint32_t rendererID;
    };
}

#endif // __OPENGL_BUFFER_H__