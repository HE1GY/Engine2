
#include "OpenGLShader.h"

#include "Engine/Log/Log.h"
#include "Engine/Utils/FileHandler.h"
#include <array>

#include <glm/gtc/type_ptr.hpp>

namespace Engine {
    static GLenum ShaderTypeFromString(const std::string& type) {
        if (type == "vertex") {
            return GL_VERTEX_SHADER;
        }
        if (type == "fragment" || type == "pixel") {
            return GL_FRAGMENT_SHADER;
        }
        CORE_ASSERT_LOG(false, "Unknown shader type!");
        return 0;
    }


    OpenGLShader::OpenGLShader(const std::string& src_path) {
        std::string src                                 = Utils::ReadFile(src_path);
        std::unordered_map<GLenum, std::string> shaders = PreProcess(src);
        Compile(shaders);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_renderer_id);
    }


    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& src) {

        std::unordered_map<GLenum, std::string> shaderSources;

        size_t token_length = strlen(k_shader_type_token);
        size_t token_pos    = src.find(k_shader_type_token);

        while (token_pos != std::string::npos) {
            size_t token_eol = src.find_first_of("\r\n", token_pos); // find end of line
            CORE_ASSERT_LOG((token_eol != std::string::npos), "Syntax error");

            size_t shader_type_begin = token_pos + token_length + 1; // pos of beginning shader type
            std::string shader_type  = src.substr(shader_type_begin, token_eol - shader_type_begin);
            CORE_ASSERT_LOG(ShaderTypeFromString(shader_type), "Invalid shader type specified");

            size_t shade_body_begin =
                src.find_first_not_of("\r\n", token_eol); // Start of shader code after shader type declaration line
            CORE_ASSERT_LOG((shade_body_begin != std::string::npos), "Syntax error");
            token_pos = src.find(k_shader_type_token, shade_body_begin); // find new token pos

            shaderSources[ShaderTypeFromString(shader_type)] =
                (token_pos == std::string::npos) ? src.substr(shade_body_begin)
                                                 : src.substr(shade_body_begin, token_pos - shade_body_begin);
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(std::unordered_map<GLenum, std::string>& shaders) {
        m_renderer_id = glCreateProgram();

        CORE_ASSERT_LOG((shaders.size() >= k_shader_count_at_least), "Too few shaders. Expected at least {0}",
            k_shader_count_at_least);
        std::vector<GLuint> shader_ids(k_shader_count_at_least);

        for (auto& shader : shaders) {
            GLenum type            = shader.first;
            const std::string& src = shader.second;

            GLuint shader_id = glCreateShader(type);

            const GLchar* source = static_cast<const GLchar*>(src.c_str());
            glShaderSource(shader_id, 1, &source, nullptr);
            glCompileShader(shader_id);

            GLint compile_status;
            glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
            if (compile_status == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> info_log(maxLength);
                glGetShaderInfoLog(shader_id, maxLength, &maxLength, &info_log[0]);

                // We don't need the shader anymore.
                glDeleteShader(shader_id);

                CORE_ERROR_LOG("Failed to compile shader");
                CORE_ERROR_LOG(info_log.data());
            }

            glAttachShader(m_renderer_id, shader_id);
            shader_ids.push_back(shader_id);
        }

        glLinkProgram(m_renderer_id);
        int link_status;
        glGetProgramiv(m_renderer_id, GL_LINK_STATUS, &link_status);
        if (link_status != GL_TRUE) {
            GLint maxLength = 0;
            glGetProgramiv(m_renderer_id, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> info_log(maxLength);
            glGetProgramInfoLog(m_renderer_id, maxLength, &maxLength, &info_log[0]);

            CORE_ERROR_LOG("Failed to link shader");
            CORE_ERROR_LOG(info_log.data());
        }

        for (auto& shader_id : shader_ids) {
            glDeleteShader(shader_id);
        }
    }

    void OpenGLShader::Bind() {
        glUseProgram(m_renderer_id);
    }

    void OpenGLShader::UnBind() {
        glUseProgram(0);
    }


    void OpenGLShader::UploadUniform(const std::string& name, float value) {
        ASSERT(m_renderer_id);

        GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniform(const std::string& name, const glm::mat4& value) {
        ASSERT(m_renderer_id);

        GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void OpenGLShader::UploadUniform(const std::string& name, const glm::vec4& value) {
        ASSERT(m_renderer_id);
        GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
        glUniform4f(location, value.r, value.g, value.b, value.a);
    }

    void OpenGLShader::UploadUniform(const std::string& name, int value) {
        ASSERT(m_renderer_id);
        GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
        glUniform1d(location, value);
    }

    void OpenGLShader::UploadUniform(const std::string& name, const int* value, uint32_t count) {
        ASSERT(m_renderer_id);
        GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
        if (location < 0) {
            CORE_WARN_LOG("Uniform {0} not found", name);
        }
        glUniform1iv(location, count, value);
    }

} // namespace Engine
