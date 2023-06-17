#pragma once
#include "Engine/LowAPI/Renderer/Shader.h"
#include <glad/glad.h>
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

namespace Engine {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& src_path);

        ~OpenGLShader() override;

        void Bind() override;
        void UnBind() override;


        void UploadUniform(const std::string& name, float value);

        void UploadUniform(const std::string& name, const glm::mat4& value);

        void UploadUniform(const std::string& name, const glm::vec4& value);

        void UploadUniform(const std::string& name, int value);

        void UploadUniform(const std::string& name, const int* value, uint32_t count);

    private:
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
        void Compile(std::unordered_map<GLenum, std::string>& shaders);

    private:
        static constexpr char const* k_shader_type_token  = "#type";
        static constexpr uint32_t k_shader_count_at_least = 2;
        uint32_t m_renderer_id;
    };

} // namespace Engine
