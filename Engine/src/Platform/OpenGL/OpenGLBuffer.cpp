#include "OpenGLBuffer.h"

#include "Engine/Log/Log.h"

namespace Engine {
    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
        glCreateBuffers(1, &m_renderer_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);

        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &m_renderer_id);
    }

    void OpenGLVertexBuffer::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    }

    void OpenGLVertexBuffer::UnBind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetData(void* data, size_t size) {
        glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }


    ///////////////////////////////////////////////////
    // indexBuff//
    //////////////////////////////////////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* data, uint32_t count) : m_count{count} {
        glCreateBuffers(1, &m_renderer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &m_renderer_id);
    }

    void OpenGLIndexBuffer::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    }

    void OpenGLIndexBuffer::UnBind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

} // namespace Engine
