#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>

namespace Kaydee {
    class Shader
    {
    public:
        virtual ~Shader() {}

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static Shader* create(const std::string& filepath);
        static Shader* create(const std::string& vertexSrc,
                              const std::string& fragmentSrc);
    };
}

#endif // __SHADER_H__