#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine {
    // TODO switch to platform selector
    Ref<VertexArray> VertexArray::Create() {
        return std::make_shared<OpenGLVertexArray>();
    }
} // namespace Engine
