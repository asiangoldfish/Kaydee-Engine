#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Platforms/OpenGL/OpenGLShader.h"
#include "RenderCommand.h"

namespace Kaydee {

    struct Renderer2DContext
    {
        ref<VertexArray> vertexArray;
        ref<Shader> shader;
    };

    static Renderer2DContext* contextData;

    void Renderer2D::init()
    {
        contextData = new Renderer2DContext();
        contextData->vertexArray = VertexArray::create();

        float squareVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f, // Bottom left
            0.5f,  -0.5f, 0.0f, // Bottom right
            0.5f,  0.5f,  0.0f, // Top right
            -0.5f, 0.5f,  0.0f  // Top left
        };

        ref<VertexBuffer> squareVB;
        squareVB.reset(
          VertexBuffer::create(squareVertices, sizeof(squareVertices)));

        squareVB->setLayout({ { ShaderDataType::Float3, "a_position" } });

        contextData->vertexArray->addVertexBuffer(squareVB);

        unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        ref<IndexBuffer> squareIB;

        squareIB.reset(IndexBuffer::create(
          squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

        contextData->vertexArray->setIndexBuffer(squareIB);

        contextData->shader =
          Shader::create("Sandbox/assets/shaders/flatColor.glsl");
    }

    void Renderer2D::shutdown()
    {
        if (contextData) {
            delete contextData;
            contextData = nullptr;
        }
    }

    void Renderer2D::beginScene(const OrthographicCamera& camera)
    {
        contextData->shader->bind();
        std::dynamic_pointer_cast<OpenGLShader>(contextData->shader)
          ->uploadUniformMat4("u_viewProjection",
                              camera.getViewProjectionMatrix());
        std::dynamic_pointer_cast<OpenGLShader>(contextData->shader)
          ->uploadUniformMat4("u_transform", glm::mat4(1.0f));
    }

    void Renderer2D::endScene() {}

    void Renderer2D::drawQuad(const glm::vec2& position,
                              const glm::vec2& size,
                              const glm::vec4& color)
    {
        drawQuad({ position.x, position.y, 1.0f }, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec3& position,
                              const glm::vec2& size,
                              const glm::vec4& color)
    {
        contextData->shader->bind();
        contextData->vertexArray->bind();
        std::dynamic_pointer_cast<OpenGLShader>(contextData->shader)
          ->uploadUniformFloat4("u_color", color);
        RenderCommand::drawIndexed(contextData->vertexArray);
    }

}
