#include "SubTexture2D.h"
#include "kdpch.h"

namespace Kaydee {
    SubTexture2D::SubTexture2D(const ref<Texture2D>& texture,
                               const glm::vec2& min,
                               const glm::vec2& max)
      : texture(texture)
    {
        texCoords[0] = { min.x, min.y };
        texCoords[1] = { max.x, min.y };
        texCoords[2] = { max.x, max.y };
        texCoords[3] = { min.x, max.y };
    }

    ref<SubTexture2D> SubTexture2D::createFromCoords(
      const ref<Texture2D>& texture,
      const glm::vec2& coords,
      const glm::vec2& size,
      const glm::vec2& spriteSize)
    {
        glm::vec2 min = { (coords.x * size.x) / texture->getWidth(),
                          (coords.y * size.y) / texture->getHeight() };
        glm::vec2 max = { ((coords.x + spriteSize.x) * size.x) / texture->getWidth(),
                          ((coords.y + spriteSize.y) * size.y) / texture->getHeight() };

        return createRef<SubTexture2D>(texture, min, max);
    }
}