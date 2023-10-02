#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Kaydee {

    struct Renderer2DContext
    {
        ref<VertexArray> vertexArray;
        ref<Shader> flatColorShader;
        ref<Shader> textureShader;
    };

    static Renderer2DContext* contextData;

    void Renderer2D::init()
    {
        contextData = new Renderer2DContext();
        contextData->vertexArray = VertexArray::create();

        float squareVertices[]= {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom left
            0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // Bottom right
            0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // Top right
            -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // Top left
        };

        ref<VertexBuffer> squareVB;
        squareVB.reset(
          VertexBuffer::create(squareVertices, sizeof(squareVertices)));

        squareVB->setLayout({ { ShaderDataType::Float3, "a_position" },
                              { ShaderDataType::Float2, "a_texCoord" } });

        contextData->vertexArray->addVertexBuffer(squareVB);

        unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        ref<IndexBuffer> squareIB;

        squareIB.reset(IndexBuffer::create(
          squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

        contextData->vertexArray->setIndexBuffer(squareIB);

        // Flat color shader
        contextData->flatColorShader =
          Shader::create("Sandbox/assets/shaders/flatColor.glsl");

        // Texture shader
        contextData->textureShader =
          Shader::create("Sandbox/assets/shaders/texture.glsl");
        contextData->textureShader->bind();
        contextData->textureShader->setInt("u_texture", 0);
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
        contextData->flatColorShader->bind();
        contextData->flatColorShader->setMat4("u_viewProjection",
                                              camera.getViewProjectionMatrix());

        contextData->textureShader->bind();
        contextData->textureShader->setMat4("u_viewProjection",
                                            camera.getViewProjectionMatrix());
    }

    void Renderer2D::endScene() {}

    void Renderer2D::drawQuad(const glm::vec2& position,
                              const glm::vec2& size,
                              const float rotation,
                              const glm::vec4& color)
    {
        drawQuad({ position.x, position.y, 0.0f }, size, rotation, color);
    }

    void Renderer2D::drawQuad(const glm::vec3& position,
                              const glm::vec2& size,
                              const float rotation,
                              const glm::vec4& color)
    {
        contextData->flatColorShader->bind();
        contextData->flatColorShader->setFloat4("u_color", color);

        glm::mat4 transform =
          glm::translate(glm::mat4(1.0f), position) *
          glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0, 0, 1 }) *
          glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        contextData->flatColorShader->setMat4("u_transform", transform);

        contextData->vertexArray->bind();
        RenderCommand::drawIndexed(contextData->vertexArray);
    }

    void Renderer2D::drawQuad(const glm::vec2& position,
                              const glm::vec2& size,
                              const float rotation,
                              const glm::vec4& color,
                              const ref<Texture2D> texture)
    {
        drawQuad(
          { position.x, position.y, 0.0f }, size, rotation, color, texture);
    }

    void Renderer2D::drawQuad(const glm::vec3& position,
                              const glm::vec2& size,
                              const float rotation,
                              const glm::vec4& color,
                              const ref<Texture2D> texture)
    {
        contextData->textureShader->bind();
        contextData->textureShader->setFloat4("u_color", color);

        glm::mat4 transform =
          glm::translate(glm::mat4(1.0f), position) *
          glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0, 0, 1 }) *
          glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        contextData->textureShader->setMat4("u_transform", transform);

        texture->bind();

        contextData->vertexArray->bind();
        RenderCommand::drawIndexed(contextData->vertexArray);
    }
}
