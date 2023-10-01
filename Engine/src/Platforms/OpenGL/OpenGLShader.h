#ifndef __OPENGL_SHADER_H__
#define __OPENGL_SHADER_H__

#include "Renderer/Shader.h"
#include <glm/glm.hpp>
#include <unordered_map>
#include <glad/glad.h>
#include <string>

namespace Kaydee {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& vertexSrc,
                     const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        void bind() const override;
        void unbind() const override;

        void uploadUniformInt(const std::string& name, int value);
        void uploadUniformFloat(const std::string& name, float value);
        void uploadUniformFloat2(const std::string& name,
                                 const glm::vec2& values);
        void uploadUniformFloat3(const std::string& name,
                                 const glm::vec3& values);
        void uploadUniformFloat4(const std::string& name,
                                 const glm::vec4& values);
        void uploadUniformMat4(const std::string& name,
                               const glm::mat4& matrix);

    private:
        std::string readFile(const std::string& filepath);

        /**
         * @brief Split shader file to identify the contained shaders
         * Unordered map: Key = GLenum, Source code = std::string
         *
         * @param source Source code from file
         */
        std::unordered_map<GLenum, std::string> preProcess(
          const std::string& source);

        void compile(
          const std::unordered_map<GLenum, std::string>& shaderSources);

        /**
         * @brief Get platform specific end of line
         */
        inline std::string getEol();

    private:
        uint32_t rendererId;
    };

}

#endif // __OPENGL_SHADER_H__