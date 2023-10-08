#include "kdpch.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace Kaydee {
    // Vertex buffer
    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
        KD_PROFILE_FUNCTION();

        glCreateBuffers(1, &rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }
    
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        KD_PROFILE_FUNCTION();

        glCreateBuffers(1, &rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        KD_PROFILE_FUNCTION();

        glDeleteBuffers(1, &rendererID);
    }

    void OpenGLVertexBuffer::bind() const
    {
        KD_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    }

    void OpenGLVertexBuffer::unbind() const
    {
        KD_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::setData(const void* data, uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    // Index buffer
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
      : count(count)
    {
        KD_PROFILE_FUNCTION();

        glCreateBuffers(1, &rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     count * sizeof(uint32_t),
                     indices,
                     GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        KD_PROFILE_FUNCTION();

        glDeleteBuffers(1, &rendererID);
    }

    void OpenGLIndexBuffer::bind() const
    {
        KD_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
    }

    void OpenGLIndexBuffer::unbind() const
    {
        KD_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}