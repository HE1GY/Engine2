#pragma once

#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

namespace Engine {
    class GraphicObjectFactory {
    public:
        virtual ~GraphicObjectFactory()                                                               = default;
        virtual Ref<VertexBuffer> CreateVertexBuffer(size_t size)                                     = 0;
        virtual Ref<IndexBuffer> CreateIndexBuffer(uint32_t* data, size_t count)                      = 0;
        virtual Ref<VertexArray> CreateVertexArray()                                                  = 0;
        virtual Ref<Texture> CreateTexture(const Texture::Properties& props, const std::string& path) = 0;
        virtual Ref<Texture> CreateTexture()                                                          = 0;
        virtual Ref<Shader> CreateShader(const std::string& path)                                     = 0;
    };
} // namespace Engine
