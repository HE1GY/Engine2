#include "Shader.h"

#include "Engine/Core/Ptrs.h"
#include "Engine/Log/Log.h"
#include "Platform/OpenGL/OpenGLShader.h"

// TODO selector
namespace Engine {
    Ref<Shader> Shader::Create(
        const std::string& name, const std::string& vertex_src, const std::string& fragment_src) {
        return CreateRef<OpenGLShader>(name, vertex_src, fragment_src);
    }

    Ref<Shader> Shader::Create(const std::string& src_path) {
        return CreateRef<OpenGLShader>(src_path);
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader) {
        const std::string& name = shader->get_name();
        Add(name, shader);
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
        CORE_ASSERT_LOG((m_shaders.find(name) == m_shaders.end()), "Shader has already been added");
        m_shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& src_path) {
        Ref<Shader> shader = Shader::Create(src_path);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& src_path) {
        Ref<Shader> shader = Shader::Create(src_path);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name) {
        CORE_ASSERT_LOG((m_shaders.find(name) != m_shaders.end()), "Shader has not been found");
        return m_shaders[name];
    }
} // namespace Engine
