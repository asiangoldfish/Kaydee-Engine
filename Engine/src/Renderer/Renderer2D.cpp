#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"

#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>

#include <vector>
#include <array>

#include "Core/Core.h"

#include "Debug/Instrumentor.h"

namespace Kaydee {

    struct QuadVertex
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 textureCoord;
        int textureIndex;
        float tilingFactor;
    };

    struct Renderer2DContext
    {
        static const uint32_t maxQuads = 20000; ///< Max quads per draw call
        static const uint32_t maxVertices = maxQuads * 4;
        static const uint32_t maxIndices = maxQuads * 6;
        static const uint32_t maxTextureSlots =
          32; // TODO - Render capabilities

        ref<VertexArray> vertexArray;
        ref<VertexBuffer> vertexBuffer;
        ref<Shader> textureShader;
        ref<Texture2D> whiteTexture;

        uint32_t quadIndexCount = 0; ///< Currently drawn quads

        QuadVertex* quadVertexBufferBase = nullptr;
        QuadVertex* quadVertexBufferPtr = nullptr;

        std::array<ref<Texture2D>, maxTextureSlots> textureSlots;
        uint32_t textureSlotIndex = 1; // 0 = white texture

        Renderer2D::Statistics stats;

        glm::vec4 quadVertexPositions[4];
    };

    static Renderer2DContext contextData;

    void Renderer2D::init()
    {
        contextData.vertexArray = VertexArray::create();

        // Vertex buffer
        contextData.vertexBuffer =
          VertexBuffer::create(contextData.maxVertices * sizeof(QuadVertex));

        contextData.vertexBuffer->setLayout(
          { { ShaderDataType::Float3, "a_position" },
            { ShaderDataType::Float4, "a_color" },
            { ShaderDataType::Float2, "a_texCoord" },
            { ShaderDataType::Int, "a_texIndex" },
            { ShaderDataType::Float, "a_tilingFactor" } });

        contextData.vertexArray->addVertexBuffer(contextData.vertexBuffer);

        contextData.quadVertexBufferBase =
          new QuadVertex[contextData.maxVertices];

        // Generate index buffer
        uint32_t* quadIndices = new uint32_t[contextData.maxIndices];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < contextData.maxIndices; i += 6) {
            if (i + 6 < contextData.maxIndices) {
                quadIndices[i + 0] = offset + 0;
                quadIndices[i + 1] = offset + 1;
                quadIndices[i + 2] = offset + 2;

                quadIndices[i + 3] = offset + 2;
                quadIndices[i + 4] = offset + 3;
                quadIndices[i + 5] = offset + 0;

                offset += 4;
            }
        }

        contextData.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        contextData.quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
        contextData.quadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
        contextData.quadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };

        ref<IndexBuffer> squareIB;
        squareIB = IndexBuffer::create(quadIndices, contextData.maxIndices);
        delete[] quadIndices;

        contextData.vertexArray->setIndexBuffer(squareIB);

        contextData.whiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        contextData.whiteTexture->setData((void*)&whiteTextureData,
                                          sizeof(uint32_t));

        // Texture shader
        contextData.textureShader =
          Shader::create("assets/shaders/texture.glsl");
        contextData.textureShader->bind();

        int32_t samplers[contextData.maxTextureSlots];
        for (uint32_t i = 0; i < contextData.maxTextureSlots; i++) {
            // contextData.textureShader->setInt("u_textures[" +
            // std::to_string(i) + "]", i);
            samplers[i] = i;
        }

        contextData.textureShader->setIntArray(
          "u_textures", samplers, contextData.maxTextureSlots);

        // Set all texture slots to 0
        contextData.textureSlots[0] = contextData.whiteTexture;

        contextData.quadIndexCount += 6;

        // Statistics
        contextData.stats.quadCount++;
    }

    void Renderer2D::shutdown()
    {
        KD_PROFILE_FUNCTION();
    }

    void Renderer2D::beginScene(const Camera& camera, const glm::mat4& transform)
    {
        KD_PROFILE_FUNCTION();

        glm::mat4 viewProj = camera.getProjection() * glm::inverse(transform);

        contextData.textureShader->bind();
        contextData.textureShader->setMat4("u_viewProjection", viewProj);

        contextData.quadIndexCount = 0;
        contextData.quadVertexBufferPtr = contextData.quadVertexBufferBase;

        contextData.textureSlotIndex = 1;
    }

    void Renderer2D::beginScene(const OrthographicCamera& camera)
    {
        KD_PROFILE_FUNCTION();

        contextData.textureShader->bind();
        contextData.textureShader->setMat4("u_viewProjection",
                                           camera.getViewProjectionMatrix());

        contextData.quadIndexCount = 0;
        contextData.quadVertexBufferPtr = contextData.quadVertexBufferBase;

        contextData.textureSlotIndex = 1;
    }

    void Renderer2D::endScene()
    {
        KD_PROFILE_FUNCTION();

        flush();
    }

    void Renderer2D::flush()
    {
        // Upload data to the GPU
        // Cast to uint8_t (a byte) so we get number of vertices in bytes
        uint32_t dataSize =
          (uint32_t)((uint8_t*)contextData.quadVertexBufferPtr -
                     (uint8_t*)contextData.quadVertexBufferBase);
        contextData.vertexBuffer->setData(contextData.quadVertexBufferBase,
                                          dataSize);

        contextData.textureShader->bind();
        // Bind textures
        for (uint32_t i = 0; i < contextData.textureSlotIndex; i++) {
            contextData.textureSlots[i]->bind(i);
        }

        RenderCommand::drawIndexed(contextData.vertexArray,
                                   contextData.quadIndexCount);
        contextData.stats.drawCalls++;
    }

    void Renderer2D::flushAndReset()
    {
        endScene();
        contextData.quadIndexCount = 0;
        contextData.quadVertexBufferPtr = contextData.quadVertexBufferBase;

        contextData.textureSlotIndex = 1;
    }

    void Renderer2D::drawQuad(const Quad2DProperties* properties)
    {
        KD_PROFILE_FUNCTION();

        // Handle edge case when we draw too many vertices
        if (contextData.quadIndexCount >= Renderer2DContext::maxIndices) {
            flushAndReset();
        }

        // --------
        // Textures
        // --------
        // If sub texture, then fetch texture coordinates from it. Otherwise,
        // default to 0 to 1 coordinate space.
        glm::vec2 texCoords[4];
        ref<Texture2D> texture;
        if (properties->subTexture) {
            memcpy(texCoords,
                   properties->subTexture->getTexCoords(),
                   sizeof(glm::vec2) * 4);
            texture = properties->subTexture->getTexture();
        } else {
            texCoords[0] = { 0.0f, 0.0f }; // 1. bottom left
            texCoords[1] = { 1.0f, 0.0f }; // 2. bottom right
            texCoords[2] = { 1.0f, 1.0f }; // 3. top right
            texCoords[3] = { 0.0f, 1.0f }; // 4. top left

            texture = properties->texture;
        };

        // Figure out whether we have bound this quad's texture before
        // constexpr glm::vec4 color(1.0f);

        uint32_t textureIndex = 0;
        for (uint32_t i = 0; i < contextData.textureSlotIndex; i++) {
            if (contextData.textureSlots[i].get() == texture.get()) {
                textureIndex = i;
                break;
            }
        }

        // If a texture was passed, then we set the corresponding textureId to
        // that texture's ID. Otherwise the ID is 0
        if (textureIndex == 0) {
            if (texture) {
                textureIndex = contextData.textureSlotIndex;
                contextData.textureSlots[contextData.textureSlotIndex] =
                  texture;
                contextData.textureSlotIndex++;
            }
        }

        // --------
        // Transformation
        // --------
        // Translate
        glm::mat4 transform;
        if (properties->transform == glm::mat4(1.0f)) {
            transform = properties->transform;
        } else {
            transform = glm::translate(glm::mat4(1.0f), properties->position);

            // Rotate
            transform = glm::rotate(
              transform, properties->rotation, { 0.0f, 0.0f, 1.0f });

            // Scale
            transform = glm::scale(transform, properties->scale);
        }

        for (int i = 0; i < 4; i++) {
            contextData.quadVertexBufferPtr->position =
              transform * contextData.quadVertexPositions[i];
            contextData.quadVertexBufferPtr->color = properties->color;
            contextData.quadVertexBufferPtr->textureCoord = texCoords[i];
            contextData.quadVertexBufferPtr->textureIndex = textureIndex;
            contextData.quadVertexBufferPtr->tilingFactor =
              properties->tilingFactor;
            contextData.quadVertexBufferPtr++;
        }

        contextData.quadIndexCount += 6;
        contextData.stats.quadCount++;

#if OLD_PATH
        // Properties
        contextData.textureShader->setFloat4("u_color", properties->color);
        contextData.textureShader->setFloat2(
          "u_tiling", glm::vec2(properties->tilingFactor));

        // Transformation matrix - position, rotation, scaling
        glm::mat4 transform = glm::mat4(1.0f);
        transform =
          glm::translate(transform, properties->position) *
          glm::rotate(transform, properties->rotation, { 0, 0, 1 }) *
          glm::scale(transform,
                     { properties->size.x, properties->size.y, 1.0f });
        contextData.textureShader->setMat4("u_transform", transform);

        Texture contextData.textureShader->setBool(
          "u_enableTexture", properties->texture ? true : false);
        if (properties->texture) {
            properties->texture->bind();
        }

        contextData.vertexArray->bind();
        RenderCommand::drawIndexed(contextData.vertexArray);

        if (properties->texture) {
            properties->texture->unbind();
        }
#endif
    }

    ref<Shader>& Renderer2D::getShader()
    {
        return contextData.textureShader;
    }

    void Renderer2D::resetStats()
    {
        memset(&contextData.stats, 0, sizeof(Statistics));
    }

    Renderer2D::Statistics Renderer2D::getStats()
    {
        return contextData.stats;
    }
}
