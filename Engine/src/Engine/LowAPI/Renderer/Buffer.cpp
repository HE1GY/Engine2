#include "Buffer.h"

#include "Engine/Log/Log.h"
#include "Platform/OpenGL/OpenGLBuffer.h"


namespace Engine {

    // TODO to utils file
    uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
        case ShaderDataType::Float:
            return 4;
        case ShaderDataType::Float2:
            return 2 * 4;
        case ShaderDataType::Float3:
            return 3 * 4;
        case ShaderDataType::Float4:
            return 4 * 4;
        case ShaderDataType::Int:
            return 4;
        case ShaderDataType::Int2:
            return 4 * 2;
        case ShaderDataType::Int3:
            return 4 * 3;
        case ShaderDataType::Int4:
            return 4 * 4;
        case ShaderDataType::Mat3:
            return 3 * 3 * 4;
        case ShaderDataType::Mat4:
            return 4 * 4 * 4;
        case ShaderDataType::Bool:
            return 1;
        default:
            CORE_ASSERT_LOG(false, "Unsupported shader type");
            return 0;
        }
    }

    BufferElement::BufferElement(ShaderDataType type, const std::string& name, bool normalized)
        : name{name}, type{type}, normalized{normalized}, offset{0}, size{0} {
        size = ShaderDataTypeSize(type);
    }

    uint32_t BufferElement::GetComponentCount() const {

        switch (type) {
        case ShaderDataType::Float:
            return 1;
        case ShaderDataType::Float2:
            return 2;
        case ShaderDataType::Float3:
            return 3;
        case ShaderDataType::Float4:
            return 4;
        case ShaderDataType::Int:
            return 1;
        case ShaderDataType::Int2:
            return 2;
        case ShaderDataType::Int3:
            return 3;
        case ShaderDataType::Int4:
            return 4;
        case ShaderDataType::Mat3:
            return 3 * 3;
        case ShaderDataType::Mat4:
            return 4 * 4;
        case ShaderDataType::Bool:
            return 1;
        default:
            CORE_ASSERT_LOG(false, "Unsupported shader type");
            return 0;
        }
    }

    BufferLayout::BufferLayout(std::initializer_list<BufferElement> layout) : m_elements{layout} {
        CalculateOffsetAndStride();
    }

    void BufferLayout::CalculateOffsetAndStride() {
        m_stride        = 0;
        uint32_t offset = 0;
        for (auto& element : m_elements) {
            element.offset = offset;
            offset += element.size;
            m_stride += element.size;
        }
    }


    // TODO switch to platform selector
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
        return CreateRef<OpenGLVertexBuffer>(size);
    }

    Ref<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size) {
        return CreateRef<OpenGLVertexBuffer>(data, size);
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* data, uint32_t count) {

        return CreateRef<OpenGLIndexBuffer>(data, count);
    }

} // namespace Engine
