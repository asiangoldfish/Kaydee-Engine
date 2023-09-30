#include "kdpch.h"
#include "Platforms/OpenGL/OpenGLTexture.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include "stb/stb_image.h"

namespace Kaydee {

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
      : path(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        unsigned char* data =
          stbi_load(path.c_str(), &width, &height, &channels, 0);

        // If stb fails to load image
        KD_CORE_ASSERT(data, "Failed to load image!");

        this->width = width;
        this->height = height;

        // Detect RGB and RGBA
        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        } else if (channels == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        KD_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

        // Upload to OpenGL
        glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
        glTextureStorage2D(
          rendererID, 1, internalFormat, this->width, this->height);

        glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(rendererID,
                            0,
                            0,
                            0,
                            this->width,
                            this->height,
                            dataFormat,
                            GL_UNSIGNED_BYTE,
                            data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &rendererID);
    }

    void OpenGLTexture2D::bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, rendererID);
    }
}