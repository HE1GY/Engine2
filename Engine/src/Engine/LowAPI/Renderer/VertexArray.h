#pragma once

#include "Buffer.h"

namespace Engine {
    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() = 0;

        virtual void UnBind() = 0;

        virtual void SetVertexBuffer(
            Ref<VertexBuffer>& vertex_buffers, std::initializer_list<GraphicDataType> layout) = 0;

        inline void SetIndexCount(size_t count) { m_index_count = count; }
        inline size_t GetIndexCount() const { return m_index_count; }

    private:
        size_t m_index_count;
    };
} // namespace Engine
