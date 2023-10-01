#include "kdpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>

namespace Kaydee {
    static GLenum shaderTypeFromString(const std::string& type)
    {
        if (type == "vertex") {
            return GL_VERTEX_SHADER;
        } else if (type == "fragment" || type == "pixel") {
            return GL_FRAGMENT_SHADER;
        }

        KD_WARN("Invalid shader type '{0}'", type);
        KD_CORE_ASSERT(false, "Unknown shader type!");
        return 0;
    }

    static std::string getEol()
    {
#ifdef _WIN32
        std::string eol = "\r\n";
#elif __APPLE__
        std::string eol = "\r";
#else
        std::string eol = "\n";
#endif
        return eol;
    }

    OpenGLShader::OpenGLShader(const std::string& filepath)
    {
        std::string source = readFile(filepath);
        auto shaderSources = preProcess(source);
        compile(shaderSources);

        // Dynamically extract name from file name
        // assets/shaders/texture.glsl
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count =
          lastDot == std::string::npos ? filepath.size() : lastDot - lastSlash;

        name = filepath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(const std::string& name,
                               const std::string& vertexSrc,
                               const std::string& fragmentSrc)
      : name(name)
    {
        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        compile(sources);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(rendererId);
    }

    std::string OpenGLShader::readFile(const std::string& filepath)
    {
        std::string result;
        std::ifstream infile(filepath, std::ios::in | std::ios::binary);

        if (infile) {
            infile.seekg(0, std::ios::end);
            result.resize(infile.tellg());
            infile.seekg(0, std::ios::beg);
            infile.read(&result[0], result.size());
            infile.close();
        } else {
            KD_CORE_ERROR("Unable to open file '{}'", filepath);
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::preProcess(
      const std::string& source)
    {
        std::unordered_map<GLenum, std::string> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);

        while (pos != std::string::npos) {
            size_t eol = source.find_first_of(getEol(), pos);

            KD_CORE_ASSERT(eol != std::string::npos, "Synax error");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            KD_CORE_ASSERT(shaderTypeFromString(type),
                           "Invalid shader type specifier");

            size_t nextLinePos = source.find_first_not_of(getEol(), eol);
            pos = source.find(typeToken, nextLinePos);
            KD_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
            shaderSources[shaderTypeFromString(type)] =
              (pos == std::string ::npos)
                ? source.substr(nextLinePos)
                : source.substr(nextLinePos, pos - nextLinePos);
        }

        return shaderSources;
    }

    void OpenGLShader::compile(
      const std::unordered_map<GLenum, std::string>& shaderSources)
    {
        GLuint program = glCreateProgram();
        KD_CORE_ASSERT(shaderSources.size() <= 2,
                       "Only two shaders are supported\n");
        std::array<GLenum, 2> glShaderIDs;
        int glShaderIDIndex = 0;

        for (auto&& [key_type, value_source] : shaderSources) {
            GLuint shader = glCreateShader(key_type);

            const GLchar* source = (const GLchar*)value_source.c_str();
            glShaderSource(shader, 1, &source, 0);

            // Compile the vertex shader
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                // We don't need the shader anymore.
                glDeleteShader(shader);

                // Use the infoLog as you see fit.
                KD_CORE_ERROR("{0}", infoLog.data());
                KD_CORE_ASSERT(false, "Shader compilation error");

                // In this simple program, we'll just leave
                break;
            }

            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++];
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of
        // glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            for (const auto& id : glShaderIDs) {
                glDeleteShader(id);
            }

            // Use the infoLog as you see fit.
            KD_CORE_ERROR("{0}", infoLog.data());
            KD_CORE_ASSERT(false, "Shader linking error");

            // In this simple program, we'll just leave
            return;
        }

        // Always detach shaders after a successful link.
        for (const auto& id : glShaderIDs) {
            glDetachShader(program, id);
        }

        rendererId = program;
    }

    void OpenGLShader::bind() const
    {
        glUseProgram(rendererId);
    }

    void OpenGLShader::unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::uploadUniformFloat(const std::string& name, float value)
    {
        glUniform1i(glGetUniformLocation(rendererId, name.c_str()), value);
    }

    void OpenGLShader::uploadUniformFloat2(const std::string& name,
                                           const glm::vec2& values)
    {
        glUniform2f(
          glGetUniformLocation(rendererId, name.c_str()), values.x, values.y);
    }

    void OpenGLShader::uploadUniformInt(const std::string& name, int value)
    {
        glUniform1i(glGetUniformLocation(rendererId, name.c_str()), value);
    }

    void OpenGLShader::uploadUniformFloat3(const std::string& name,
                                           const glm::vec3& values)
    {
        glUniform3f(glGetUniformLocation(rendererId, name.c_str()),
                    values.x,
                    values.y,
                    values.z);
    }

    void OpenGLShader::uploadUniformFloat4(const std::string& name,
                                           const glm::vec4& values)
    {
        glUniform4f(glGetUniformLocation(rendererId, name.c_str()),
                    values.x,
                    values.y,
                    values.z,
                    values.w);
    }

    void OpenGLShader::uploadUniformMat4(const std::string& name,
                                         const glm::mat4& matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(rendererId, name.c_str()),
                           1,
                           GL_FALSE,
                           glm::value_ptr(matrix));
    }
}