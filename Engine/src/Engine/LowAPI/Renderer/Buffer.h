#pragma once

#include "Engine/Core/Ptrs.h"
#include <string>
#include <vector>

namespace Engine {
    enum class GraphicDataType {
        Float2,
        Float3,
    };

    class VertexBuffer {
    public:
        virtual ~VertexBuffer()                       = default;
        virtual void Bind()                           = 0;
        virtual void UnBind()                         = 0;
        virtual void SetData(void* data, size_t size) = 0;
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer()      = default;
        virtual void Bind()         = 0;
        virtual void UnBind()       = 0;
        virtual uint32_t GetCount() = 0;
    };
} // namespace Engine
