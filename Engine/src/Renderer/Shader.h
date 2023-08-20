#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>

namespace Kaydee {
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~Shader();

        void bind() const;
        void unbind() const;

    private:
        uint32_t rendererId;
    };
}

#endif // __SHADER_H__