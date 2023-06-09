#pragma once

#include "VertexArray.h"
#include <cstdint>

#include "glm/vec4.hpp"

namespace Engine {
    class RendererCommand {
    public:
        static void Init();

        static void DrawIndex(Ref<VertexArray>& vertex_array);

        static void Clear();

        static void SetClearColor(const glm::vec4& color);

        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    };
} // namespace Engine
