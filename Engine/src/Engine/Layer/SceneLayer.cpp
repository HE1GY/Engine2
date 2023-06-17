#include "SceneLayer.h"

#include "Engine/LowAPI/Renderer/Renderer2D.h"
#include "Engine/LowAPI/Renderer/RendererCommand.h"


namespace Engine {
    void SceneLayer::OnAttach(Engine::WindowEvents& events) {
        RendererCommand::SetClearColor({1, 1, 1, 1});
    }

    void SceneLayer::OnDetach(WindowEvents& events) {
    }

    void SceneLayer::OnUpdate() {
        RendererCommand::Clear();


        Renderer2D::DrawQuad();
    }

} // namespace Engine
