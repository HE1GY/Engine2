#include "Engine/LowAPI/Renderer/RendererCommand.h"
#include "glad/glad.h"


namespace Engine {
    // TODO also create by factory
    void RendererCommand::Init() {
        // glEnable(GL_DEPTH_TEST);//TODO alpha blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_LINE_SMOOTH);
    }

    void RendererCommand::SetClearColor(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RendererCommand::DrawIndex(Ref<VertexArray>& vertex_array) {
        vertex_array->Bind();
        glDrawElements(GL_TRIANGLES, vertex_array->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
    }


    void RendererCommand::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RendererCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(x, y, width, height);
    }

} // namespace Engine
