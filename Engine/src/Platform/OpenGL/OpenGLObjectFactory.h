#pragma once
#include "Engine/LowAPI/Renderer/GraphicObjectFactory.h"
#include "Engine/LowAPI/Renderer/Shader.h"

namespace Engine {
    class OpenGLObjectFactory : public GraphicObjectFactory {
        Ref<VertexBuffer> CreateVertexBuffer(size_t size) override;
        Ref<IndexBuffer> CreateIndexBuffer(uint32_t* data, size_t count) override;
        Ref<VertexArray> CreateVertexArray() override;
        Ref<Texture> CreateTexture() override;
        Ref<Shader> CreateShader(const std::string& path) override;
    };
} // namespace Engine
