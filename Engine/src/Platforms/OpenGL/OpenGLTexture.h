#ifndef __OPENGL_TEXTURE_H__
#define __OPENGL_TEXTURE_H__

#include "Renderer/Texture.h"
#include <string>
#include <glad/glad.h>

namespace Kaydee {

    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();

        virtual uint32_t getWidth() const override { return width; }
        virtual uint32_t getHeight() const override { return height; }

        virtual void bind(uint32_t slot = 0) const override;
        virtual void unbind(uint32_t slot = 0) const override;

        virtual void setData(void* data, uint32_t size) override;
        
        virtual bool operator==(const Texture& other) const override
        {
            return rendererID == ((OpenGLTexture2D&)other).rendererID;
        }

    private:
        std::string path;
        uint32_t width, height, rendererID;
        GLenum internalFormat, dataFormat;
    };
}

#endif // __OPENGL_TEXTURE_H__