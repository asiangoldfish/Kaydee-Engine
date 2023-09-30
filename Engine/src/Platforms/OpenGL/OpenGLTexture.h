#ifndef __OPENGL_TEXTURE_H__
#define __OPENGL_TEXTURE_H__

#include "Renderer/Texture.h"
#include <string>

namespace Kaydee {

    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();

        virtual uint32_t getWidth() const override { return width; }
        virtual uint32_t getheight() const override { return height; }

        virtual void bind(uint32_t slot = 0) const override;

    private:
        std::string path;
        uint32_t width, height, rendererID;
    };
}

#endif // __OPENGL_TEXTURE_H__