
#include "OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include "Engine/Log/Log.h"
#include <array>

#include <fstream>

namespace Engine
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		CORE_ASSERT_LOG(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex_src, const std::string& fragment_src)
	  : m_name{ name }
	{

		std::unordered_map<GLuint, std::string> shaders;
		shaders[GL_VERTEX_SHADER] = vertex_src;
		shaders[GL_FRAGMENT_SHADER] = fragment_src;
		Compile(shaders);
	}

	OpenGLShader::OpenGLShader(const std::string& src_path)
	{
		std::string src = ReadFile(src_path);
		auto shaders = PreProcess(src);
		Compile(shaders);

		auto last_slash = src_path.find_last_of("/\\");
		last_slash = last_slash == std::string::npos ? 0 : last_slash + 1;
		auto last_dot = src_path.rfind('.');
		auto count = last_dot == std::string::npos ? src_path.size() - last_slash : last_dot - last_slash;
		m_name = src_path.substr(last_slash, count);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_renderer_id);
	}

	std::string OpenGLShader::ReadFile(const std::string& path)
	{


		std::ifstream in(path.c_str(), std::ios_base::binary | std::ios_base::in);
		std::string result;
		if (in.is_open())
		{
			in.seekg(0, std::ios_base::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios_base::beg);
			in.read(&result[0], result.size());
		}
		else
		{
			CORE_ERROR_LOG("Shader file can't be opened {0}", path);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& src)
	{

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = src.find(typeToken, 0); // Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = src.find_first_of("\r\n", pos); // End of shader type declaration line
			CORE_ASSERT_LOG((eol != std::string::npos), "Syntax error");
			size_t begin = pos + typeTokenLength + 1; // Start of shader type name (after "#type " keyword)
			std::string type = src.substr(begin, eol - begin);
			CORE_ASSERT_LOG(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos =
			  src.find_first_not_of("\r\n", eol); // Start of shader code after shader type declaration line
			CORE_ASSERT_LOG((nextLinePos != std::string::npos), "Syntax error");
			pos = src.find(typeToken, nextLinePos); // Start of next shader type declaration line

			shaderSources[ShaderTypeFromString(type)] =
			  (pos == std::string::npos) ? src.substr(nextLinePos) : src.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(std::unordered_map<GLenum, std::string>& shaders)
	{
		m_renderer_id = glCreateProgram();
		CORE_ASSERT_LOG((shaders.size() >= 2), "too few shaders");
		std::array<GLuint, 2> shaders_id;
		uint8_t index{ 0 };
		for (auto src_shader: shaders)
		{
			GLenum type = src_shader.first;
			const std::string& src = src_shader.second;

			GLuint shader = glCreateShader(type);

			const GLchar* source = (const GLchar*)src.c_str();
			glShaderSource(shader, 1, &source, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				CORE_ERROR_LOG("Shader doesn't compile");
				CORE_ERROR_LOG(infoLog.data());
				CORE_WARN_LOG(src);
				ASSERT(false);
			}
			glAttachShader(m_renderer_id, shader);
			shaders_id[index++] = shader;
		}

		glLinkProgram(m_renderer_id);

		GLint isLinked = 0;
		glGetProgramiv(m_renderer_id, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_renderer_id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_renderer_id, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_renderer_id);
			// Don't leak shaders either.
			for (auto shader_id: shaders_id)
			{
				glDeleteShader(shader_id);
			}

			CORE_ERROR_LOG("Shader program doesn't linked");
			CORE_ERROR_LOG(infoLog.data());
			ASSERT(false);
		}

		for (auto shader_id: shaders_id)
		{
			glDetachShader(m_renderer_id, shader_id);
		}
	}

	void OpenGLShader::UploadUniform(const std::string& name, float value)
	{
		ASSERT(m_renderer_id);

		GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::mat4& value)
	{
		ASSERT(m_renderer_id);

		GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::vec4& value)
	{
		ASSERT(m_renderer_id);
		GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
		glUniform4f(location, value.r, value.g, value.b, value.a);
	}

	void OpenGLShader::UploadUniform(const std::string& name, int value)
	{
		ASSERT(m_renderer_id);
		GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
		glUniform1d(location, value);
	}

	void OpenGLShader::UploadUniform(const std::string& name, const int* value, uint32_t count)
	{
		ASSERT(m_renderer_id);
		GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
		if (location < 0)CORE_WARN_LOG("Uniform {0} not found", name);
		glUniform1iv(location, count, value);
	}

	void OpenGLShader::Bind() const
	{


		glUseProgram(m_renderer_id);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& mat)
	{

		UploadUniform(name, mat);
	}

	void OpenGLShader::SetVec4(const std::string& name, const glm::vec4& vec)
	{


		UploadUniform(name, vec);
	}

	void OpenGLShader::SetInt(const std::string& name, const int value)
	{


		UploadUniform(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, const int* value, uint32_t count)
	{

		UploadUniform(name, value, count);
	}

} // namespace Engine