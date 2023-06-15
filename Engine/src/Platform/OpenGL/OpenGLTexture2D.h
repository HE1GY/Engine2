#pragma once


#include "Engine/LowAPI/Renderer/Texture.h"
typedef unsigned int GLenum;

namespace Engine {
    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(const std::string& path);

        OpenGLTexture2D(uint32_t width, uint32_t height);

        virtual ~OpenGLTexture2D() override;

        virtual void SetData(void* data, uint32_t size) override;

        virtual void Bind(uint32_t slot = 0) override;

        virtual uint32_t GetRendererId() {
            return m_renderer_id;
        }

        uint32_t GetWidth() const override {
            return m_width;
        }

        uint32_t GetHeight() const override {
            return m_height;
        }

        std::string m_path;
        uint32_t m_height;
        uint32_t m_width;
        uint32_t m_renderer_id;
        GLenum m_internal_format;
        GLenum m_data_format;
    };
} // namespace Engine
