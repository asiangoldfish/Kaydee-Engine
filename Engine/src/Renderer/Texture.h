#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <cstdint>

namespace Kaydee {
    class Texture2D;

    class Texture
    {
    public:
        Texture() = default;
        virtual ~Texture() = default;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;

        virtual void bind(uint32_t slot = 0) const = 0;
        virtual void unbind(uint32_t slot = 0) const = 0;

        virtual void setData(void* data, uint32_t size) = 0;

        virtual bool operator==(const Texture& other) const = 0;

    };

    class Texture2D : public Texture
    {
    public:
        static ref<Texture2D> create(uint32_t width, uint32_t height);
        static ref<Texture2D> create(const std::string& path);
    };
}

#endif // __TEXTURE_H__