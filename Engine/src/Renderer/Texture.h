#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <cstdint>

namespace Kaydee {
    class Texture
    {
    public:
        Texture() = default;
        virtual ~Texture() = default;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getheight() const = 0;
        virtual void bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static ref<Texture2D> create(const std::string& path);
    };
}

#endif // __TEXTURE_H__