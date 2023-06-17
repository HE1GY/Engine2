#include "SceneLayer.h"

#include "Engine/Core/Time.h"
#include "Engine/LowAPI/Renderer/Renderer2D.h"
#include "Engine/LowAPI/Renderer/RendererCommand.h"


namespace Engine {
    void SceneLayer::OnAttach(Engine::WindowEvents& events) {
        RendererCommand::SetClearColor({0.2f, 0.3f, 0.3f, 1.0f});
    }

    void SceneLayer::OnDetach(WindowEvents& events) {
    }

    void SceneLayer::OnUpdate() {
        RendererCommand::Clear();

        /*if (m_color.r > 1) {
            m_rising = false;
        } else if (m_color.r < 0) {
            m_rising


         * * * =

         * * true;
        }

        if (m_rising) {
            m_color.r += Time::s_delta_time;
 }

         * * else
         * {


         * * m_color.r -= Time::s_delta_time;
        }*/


        Renderer2D::DrawQuad(m_color);
    }

} // namespace Engine
