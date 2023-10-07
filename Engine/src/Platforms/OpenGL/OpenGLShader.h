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
        OpenGLShader(const std::string& name,
                     const std::string& vertexSrc,
                     const std::string& fragmentSrc);

        virtual ~OpenGLShader();

        void bind() const override;
        void unbind() const override;

        virtual void setInt(const std::string& name, const int value) override;
        virtual void setFloat2(const std::string& name,
                               const glm::vec2& value) override;
        virtual void setFloat3(const std::string& name,
                               const glm::vec3& value) override;
        virtual void setFloat4(const std::string& name,
                               const glm::vec4& value) override;
        virtual void setMat4(const std::string& name,
                             const glm::mat4& value) override;
        virtual void setBool(const std::string& name,
                             const bool value) override;

        virtual const std::string& getName() const override { return name; }

        //-----------
        // Uniforms
        //-----------
        // Ints
        void uploadUniformInt(const std::string& name, int value);

        // Floats
        void uploadUniformFloat(const std::string& name, float value);
        void uploadUniformFloat2(const std::string& name,
                                 const glm::vec2& values);
        void uploadUniformFloat3(const std::string& name,
                                 const glm::vec3& values);
        void uploadUniformFloat4(const std::string& name,
                                 const glm::vec4& values);

        // Mats
        void uploadUniformMat4(const std::string& name,
                               const glm::mat4& matrix);
        void uploadUniformBool(const std::string& name, const bool value);

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

        std::string name;

    private:
        uint32_t rendererId;
    };

}

#endif // __OPENGL_SHADER_H__