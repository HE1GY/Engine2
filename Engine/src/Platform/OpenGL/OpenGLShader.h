#pragma once

#include "Engine/LowAPI//Renderer/Shader.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <string>
#include <unordered_map>

namespace Engine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertex_src, const std::string& fragment_src);

		OpenGLShader(const std::string& src_path);

		~OpenGLShader() override;

		virtual void Bind() const override;

		virtual const std::string& get_name() const override
		{
			return m_name;
		};

		virtual void SetMat4(const std::string& name, const glm::mat4& mat) override;

		virtual void SetVec4(const std::string& name, const glm::vec4& vec) override;

		virtual void SetInt(const std::string& name, const int value) override;

		virtual void SetIntArray(const std::string& name, const int* value, uint32_t count) override;

		void UploadUniform(const std::string& name, float value);

		void UploadUniform(const std::string& name, const glm::mat4& value);

		void UploadUniform(const std::string& name, const glm::vec4& value);

		void UploadUniform(const std::string& name, const int value);

		void UploadUniform(const std::string& name, const int* value, uint32_t count);

	private:
		std::string ReadFile(const std::string& path);

		std::unordered_map <GLenum, std::string> PreProcess(const std::string& src);

		void Compile(std::unordered_map <GLenum, std::string>& shaders);

	private:
		uint32_t m_renderer_id;
		std::string m_name;
	};

} // namespace Engine