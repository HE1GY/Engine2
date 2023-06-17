#pragma once


#include "Engine/LowAPI/Renderer/Texture.h"
typedef unsigned int GLenum;

namespace Engine {
    class OpenGLTexture : public Texture {
    public:
        OpenGLTexture(const Texture::Properties& props, const std::string& path);

        OpenGLTexture();

        ~OpenGLTexture() override;

        void Bind(uint32_t slot = 0) override;

        inline uint32_t GetRendererId() override {
            return m_renderer_id;
        }

        inline uint32_t GetWidth() const override {
            return m_width;
        }

        inline uint32_t GetHeight() const override {
            return m_height;
        }


    private:
        void Configure();
        Texture::Properties m_properties;
        int32_t m_height, m_width;
        uint32_t m_renderer_id;
    };
} // namespace Engine
