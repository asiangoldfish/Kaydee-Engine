#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <glm/glm.hpp>

namespace Kaydee {
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~Shader();

        void bind() const;
        void unbind() const;

        void uploadUniformFloat4(const std::string& name,
                                 const glm::vec4& values);
        void uploadUniformMat4(const std::string& name,
                               const glm::mat4& matrix);

    private:
        uint32_t rendererId;
    };
}

#endif // __SHADER_H__