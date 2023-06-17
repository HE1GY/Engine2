#include "OpenGLVertexArray.h"

#include "Engine/Log/Log.h"
#include <algorithm>
#include <glad/glad.h>


namespace Engine {
    static GLenum GraphicDataTypeToOpenGL(GraphicDataType type) {
        switch (type) {
        case GraphicDataType::Float2:
        case GraphicDataType::Float3:
            return GL_FLOAT;
        default:
            CORE_ASSERT_LOG(false, "Unknown Graphic Data Type");
            return 0;
        }
    }
    static GLint GraphicDataTypeCount(GraphicDataType type) {
        switch (type) {
        case GraphicDataType::Float2:
            return 2;
        case GraphicDataType::Float3:
            return 3;
        default:
            CORE_ASSERT_LOG(false, "Unknown Graphic Data Type");
            return 0;
        }
    }
    static GLint GraphicDataTypeSize(GraphicDataType type) {
        switch (type) {
        case GraphicDataType::Float2:
        case GraphicDataType::Float3:
            return GraphicDataTypeCount(type) * sizeof(float);
        default:
            CORE_ASSERT_LOG(false, "Unknown Graphic Data Type");
            return 0;
        }
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        glCreateVertexArrays(1, &m_renderer_id);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &m_renderer_id);
    }

    void OpenGLVertexArray::Bind() {
        glBindVertexArray(m_renderer_id);
    }

    void OpenGLVertexArray::UnBind() {
        glBindVertexArray(0);
    }


    void OpenGLVertexArray::SetVertexBuffer(
        Ref<VertexBuffer>& vertex_buffer, std::initializer_list<GraphicDataType> layout) {
        glBindVertexArray(m_renderer_id);
        vertex_buffer->Bind();

        GLsizei stride{0};
        std::for_each(layout.begin(), layout.end(), [&stride](auto& type) { stride += GraphicDataTypeSize(type); });

        uint32_t offset{0};
        uint32_t attrib_count{0};
        for (const auto& attrib : layout) {
            glEnableVertexAttribArray(attrib_count);
            glVertexAttribPointer(attrib_count, GraphicDataTypeCount(attrib), GraphicDataTypeToOpenGL(attrib), GL_FALSE,
                stride, (GLenum*) static_cast<uint64_t>(offset));
            attrib_count++;
            offset += GraphicDataTypeSize(attrib);
        }
    }

} // namespace Engine
