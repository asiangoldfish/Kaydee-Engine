#pragma once

#include "Texture.h"
#include "glm/glm.hpp"
#include "Core/Core.h"

namespace Kaydee {

    /**
     * @brief A part of a larger texture object.
     * @description Sub textures allows storing a smaller part of a texture,
     * like a spritesheet, enabling reuse of the texture. This promotes
     * resource efficiency and better maintainability.
     */
    class SubTexture2D
    {
    public:
        /**
         * @brief Constructor for new sub texture.
         * @param texture Texture to reference
         * @param min Start pixels for the sub texture
         * @param max End pixels for the sub texture
         */
        SubTexture2D(const ref<Texture2D>& texture,
                     const glm::vec2& min,
                     const glm::vec2& max);

        const ref<Texture2D> getTexture() const { return texture; }
        const glm::vec2* getTexCoords() const { return texCoords; }

        /**
         * @brief Create a sub texture as if it's its own texture.
         * @param x Sub texture starting position
         * @param size Sub texture size
         * @param spriteSize Effectively this acts as an extended sub texture
         * @return Reference to the sub texture object.
         *
         * @example spriteSize = glm::vec2(1, 2). This effectively makes the
         * subtexture twice as high. Useful for rendering trees, etc.
         */
        static ref<SubTexture2D> createFromCoords(
          const ref<Texture2D>& texture,
          const glm::vec2& coords,
          const glm::vec2& size,
          const glm::vec2& spriteSize = { 1, 1 });

    private:
        ref<Texture2D> texture;

        glm::vec2 texCoords[4];
    };
}
