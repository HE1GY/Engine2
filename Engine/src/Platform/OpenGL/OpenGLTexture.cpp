#include "OpenGLTexture.h"

#include "Engine/Log/Log.h"
#include "Engine/Utils/ImageLoader.h"
#include "stb_image.h"
#include <glad/glad.h>


namespace Engine {
    static GLint WrappingToOpenGL(Texture::Wrapping wrapping) {
        switch (wrapping) {
        case Texture::Wrapping::Repeat:
            return GL_REPEAT;
        case Texture::Wrapping::MirroredRepeat:
            return GL_MIRRORED_REPEAT;
            break;
        case Texture::Wrapping::ClampToEdge:
            return GL_CLAMP_TO_EDGE;
            break;
        case Texture::Wrapping::ClampToBorder:
            return GL_CLAMP_TO_BORDER;
            break;
        default:
            CORE_ASSERT_LOG(false, "Unknown wrapping type");
        }
    }

    static GLint FilteringToOpenGL(Texture::Filtering filtering) {
        switch (filtering) {
        case Texture::Filtering::Nearest:
            return GL_NEAREST;
        case Texture::Filtering::Linear:
            return GL_LINEAR;
        default:
            CORE_ASSERT_LOG(false, "Unknown filtering type");
        }
    }

    static GLint MipmapsToOpenGL(Texture::Mipmaps mipmaps) {
        switch (mipmaps) {
        case Texture::Mipmaps::NearestNearest:
            return GL_NEAREST_MIPMAP_NEAREST;
        case Texture::Mipmaps::LinearLinear:
            return GL_LINEAR_MIPMAP_LINEAR;
        case Texture::Mipmaps::LinearNearest:
            return GL_LINEAR_MIPMAP_NEAREST;
        case Texture::Mipmaps::NearestLinear:
            return GL_NEAREST_MIPMAP_LINEAR;
        default:
            CORE_ASSERT_LOG(false, "Unknown mipmaps type");
        }
    }


    OpenGLTexture::OpenGLTexture(const Texture::Properties& props, const std::string& path) : m_properties(props) {

        Ref<Utils::ImageProperties> image;
        Utils::LoadImage(path, image);
        m_width  = image->width;
        m_height = image->height;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);

        Configure();

        GLint internal_format = image->channels == 3 ? GL_RGB8 : GL_RGBA8;
        GLint data_format     = image->channels == 3 ? GL_RGB : GL_RGBA;

        glTextureStorage2D(m_renderer_id, 1, internal_format, m_width, m_height);
        glTextureSubImage2D(m_renderer_id, 0, 0, 0, m_width, m_height, data_format, GL_UNSIGNED_BYTE, image->data);
    }

    OpenGLTexture::OpenGLTexture() : m_width{1}, m_height{1} {
        uint32_t data = 0xffffffff;
        glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);
        glBindTexture(GL_TEXTURE_2D, m_renderer_id);
        glTextureStorage2D(m_renderer_id, 1, GL_RGBA8, m_width, m_height);
        glTextureSubImage2D(m_renderer_id, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, &data);
    }

    OpenGLTexture::~OpenGLTexture() {
        glDeleteTextures(1, &m_renderer_id);
    }

    void OpenGLTexture::Bind(uint32_t slot) {
        glBindTextureUnit(slot, m_renderer_id);
    }

    void OpenGLTexture::Configure() {

        if (m_properties.use_mipmaps) {
            glTextureParameteri(m_renderer_id, GL_TEXTURE_MIN_FILTER, MipmapsToOpenGL(m_properties.mipmaps));
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            glTextureParameteri(m_renderer_id, GL_TEXTURE_MIN_FILTER, FilteringToOpenGL(m_properties.min));
        }
        glTextureParameteri(m_renderer_id, GL_TEXTURE_MAG_FILTER, FilteringToOpenGL(m_properties.mag));

        glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_S, WrappingToOpenGL(m_properties.wrapS));
        glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_T, WrappingToOpenGL(m_properties.wrapT));
    }
} // namespace Engine
