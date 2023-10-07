#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Kaydee {

    struct Renderer2DContext
    {
        ref<VertexArray> vertexArray;
        ref<Shader> textureShader;
        ref<Texture2D> whiteTexture;
    };

    static Renderer2DContext* contextData;

    void Renderer2D::init()
    {
        contextData = new Renderer2DContext();
        contextData->vertexArray = VertexArray::create();

        float squareVertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom left
            0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // Bottom right
            0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // Top right
            -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // Top left
        };

        ref<VertexBuffer> squareVB;
        squareVB = VertexBuffer::create(squareVertices, sizeof(squareVertices));

        squareVB->setLayout({ { ShaderDataType::Float3, "a_position" },
                              { ShaderDataType::Float2, "a_texCoord" } });

        contextData->vertexArray->addVertexBuffer(squareVB);

        unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        ref<IndexBuffer> squareIB;

        squareIB = IndexBuffer::create(
          squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

        contextData->vertexArray->setIndexBuffer(squareIB);

        contextData->whiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        contextData->whiteTexture->setData((void*)&whiteTextureData,
                                           sizeof(uint32_t));

        // Texture shader
        contextData->textureShader =
          Shader::create("assets/shaders/texture.glsl");
        contextData->textureShader->bind();
        contextData->textureShader->setInt("u_texture", 0);
    }

    void Renderer2D::shutdown()
    {
        KD_PROFILE_FUNCTION();

        if (contextData) {
            delete contextData;
            contextData = nullptr;
        }
    }

    void Renderer2D::beginScene(const OrthographicCamera& camera)
    {
        KD_PROFILE_FUNCTION();

        contextData->textureShader->bind();
        contextData->textureShader->setMat4("u_viewProjection",
                                            camera.getViewProjectionMatrix());
    }

    void Renderer2D::endScene()
    {
        KD_PROFILE_FUNCTION();
    }

    void Renderer2D::drawQuad(const Quad2DProperties* properties)
    {
        KD_PROFILE_FUNCTION();

        // Properties
        contextData->textureShader->setFloat4("u_color", properties->color);
        contextData->textureShader->setFloat2(
          "u_tiling", glm::vec2(properties->tilingFactor));

        // Transformation matrix - position, rotation, scaling
        glm::mat4 transform = glm::mat4(1.0f);
        transform =
          glm::translate(transform, properties->position) *
          glm::rotate(transform, properties->rotation, { 0, 0, 1 }) *
          glm::scale(transform,
                     { properties->size.x, properties->size.y, 1.0f });
        contextData->textureShader->setMat4("u_transform", transform);

        // Texture
        contextData->textureShader->setBool("u_enableTexture",
                                            properties->texture ? true : false);
        if (properties->texture) {
            properties->texture->bind();
        }

        contextData->vertexArray->bind();
        RenderCommand::drawIndexed(contextData->vertexArray);

        if (properties->texture) {
            properties->texture->unbind();
        }
    }

    ref<Shader>& Renderer2D::getShader()
    {
        return contextData->textureShader;
    }

}
