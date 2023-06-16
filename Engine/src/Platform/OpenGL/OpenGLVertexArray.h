#pragma once

#include "Engine/LowAPI/Renderer/VertexArray.h"

namespace Engine {
    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();

        ~OpenGLVertexArray() override;

        virtual void Bind() override;

        virtual void UnBind() override;

        virtual void SetVertexBuffer(
            Ref<VertexBuffer>& vertexBuffer, std::initializer_list<GraphicDataType> layout) override;

    private:
        uint32_t m_renderer_id;
    };

} // namespace Engine
