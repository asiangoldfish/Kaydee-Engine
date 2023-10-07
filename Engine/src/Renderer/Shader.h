#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Kaydee {
    class Shader
    {
    public:
        virtual ~Shader() {}

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void setInt(const std::string& name, const int value) = 0;
        virtual void setFloat2(const std::string& name,
                               const glm::vec2& value) = 0;
        virtual void setFloat3(const std::string& name,
                               const glm::vec3& value) = 0;
        virtual void setFloat4(const std::string& name,
                               const glm::vec4& value) = 0;
        virtual void setMat4(const std::string& name,
                             const glm::mat4& value) = 0;
        virtual void setBool(const std::string& name, const bool value) = 0;

        virtual const std::string& getName() const = 0;

        static ref<Shader> create(const std::string& filepath);

        static ref<Shader> create(const std::string& name,
                                  const std::string& vertexSrc,
                                  const std::string& fragmentSrc);
    };

    class ShaderLibrary
    {
    public:
        void add(const ref<Shader>& shader);
        void add(const std::string& name, const ref<Shader>& shader);

        /**
         * @brief Load shader to the engine
         * @details The default shader name is the file name w/o the extension.
         *
         * @param filepath Relative or absolute file path
         * @return ref<Shader> Reference to the loaded shader
         */
        ref<Shader> load(const std::string& filepath);
        ref<Shader> load(const std::string& name, const std::string& filepath);

        ref<Shader> get(const std::string& name);

        bool shaderExists(const std::string& name) const;

    private:
        std::unordered_map<std::string, ref<Shader>> shaders;
    };
}

#endif // __SHADER_H__