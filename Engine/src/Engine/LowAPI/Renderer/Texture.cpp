
#include <Platform/OpenGL/OpenGLTexture2D.h>

namespace Engine {
    Ref<Texture2D> Texture2D::Create(const std::string& path) {
        return CreateRef<OpenGLTexture2D>(path);
    }

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
        return CreateRef<OpenGLTexture2D>(width, height);
    }
} // namespace Engine
