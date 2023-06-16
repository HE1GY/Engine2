#include "OpenGLObjectFactory.h"

#include "OpenGLBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLVertexArray.h"


namespace Engine {
    Ref<VertexBuffer> OpenGLObjectFactory::CreateVertexBuffer(size_t size) {
        return CreateRef<OpenGLVertexBuffer>(size);
    }
    Ref<IndexBuffer> OpenGLObjectFactory::CreateIndexBuffer(uint32_t* data, size_t count) {
        return CreateRef<OpenGLIndexBuffer>(data, count);
    }
    Ref<VertexArray> OpenGLObjectFactory::CreateVertexArray() { return CreateRef<OpenGLVertexArray>(); }

    Ref<Texture> OpenGLObjectFactory::CreateTexture() { return Engine::Ref<Texture>(); }

    Ref<Shader> OpenGLObjectFactory::CreateShader(const std::string& path) { return CreateRef<OpenGLShader>(path); }
} // namespace Engine
