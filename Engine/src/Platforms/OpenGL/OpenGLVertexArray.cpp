#include "kdpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Kaydee {

    static GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type) {
            case ShaderDataType::Float:
                return GL_FLOAT;
            case ShaderDataType::Float2:
                return GL_FLOAT;
            case ShaderDataType::Float3:
                return GL_FLOAT;
            case ShaderDataType::Float4:
                return GL_FLOAT;
            case ShaderDataType::Mat3:
                return GL_FLOAT;
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
                return GL_INT;
            case ShaderDataType::Int2:
                return GL_INT;
            case ShaderDataType::Int3:
                return GL_INT;
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
        }

        KD_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        KD_PROFILE_FUNCTION();

        glCreateVertexArrays(1, &rendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        KD_PROFILE_FUNCTION();

        glDeleteVertexArrays(1, &rendererID);
    }

    void OpenGLVertexArray::bind() const
    {
        KD_PROFILE_FUNCTION();

        glBindVertexArray(rendererID);
    }

    void OpenGLVertexArray::unbind() const
    {
        KD_PROFILE_FUNCTION();

        glBindVertexArray(0);
    }

    void OpenGLVertexArray::addVertexBuffer(
      const ref<VertexBuffer>& vertexBuffer)
    {
        glBindVertexArray(rendererID);
        vertexBuffer->bind();

        KD_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(),
                       "Vertex Buffer has no layout!");

        uint32_t index = 0;
        const auto& layout = vertexBuffer->getLayout();
        for (const auto& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  element.getComponentCount(),
                                  shaderDataTypeToOpenGLBaseType(element.type),
                                  element.normalized ? GL_TRUE : GL_FALSE,
                                  layout.getStride(),
                                  (const void*)element.offset);

            index++;
        }

        vertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::setIndexBuffer(
      const ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(rendererID);
        indexBuffer->bind();

        this->indexBuffer = indexBuffer;
    }
}