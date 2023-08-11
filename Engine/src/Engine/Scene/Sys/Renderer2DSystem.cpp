#include "Renderer2DSystem.h"

#include "Engine/LowAPI/Renderer/Renderer2D.h"
#include "Engine/LowAPI/Renderer/RendererCommand.h"
#include "Engine/Scene/Components.h"


namespace Engine {

    Renderer2DSystem::Renderer2DSystem(Coordinator& coord) : m_coord{coord} {
        RendererCommand::SetClearColor({0.2, 0.3, 0.3, 1});
    }

    void Renderer2DSystem::Update() {

        RendererCommand::Clear();

        // TODO to slow
        std::vector<Entity> sorted_entity;
        sorted_entity.reserve(sorted_entity.size());
        std::copy(m_filtered_entities.begin(), m_filtered_entities.end(), std::back_inserter(sorted_entity));
        std::sort(sorted_entity.begin(), sorted_entity.end(), [this](Entity e1, Entity e2) {
            auto& sprite1 = m_coord.GetComponent<CSpriteRenderer>(e1);
            auto& sprite2 = m_coord.GetComponent<CSpriteRenderer>(e2);
            return sprite1.priority < sprite2.priority;
        });

        for (auto& e : sorted_entity) {
            auto& transform = m_coord.GetComponent<CTransform>(e);
            auto& sprite    = m_coord.GetComponent<CSpriteRenderer>(e);

            CTransform draw_trans;

            draw_trans.position.x = ((transform.position.x / static_cast<float>(m_window_width)) * 2.0f) - 1.0f;
            draw_trans.position.y = 1.0f - ((transform.position.y / static_cast<float>(m_window_height)) * 2.0f);

            draw_trans.scale.x = transform.scale.x / (m_window_width / 2.0);
            draw_trans.scale.y = transform.scale.y / (m_window_height / 2.0);

            Renderer2D::DrawQuad(draw_trans.GetTransform(), sprite.color, sprite.texture);
        }
    }


    void Renderer2DSystem::OnWindowResize(const WindowResized& wr) {
        m_window_height = wr.height;
        m_window_width  = wr.width;
    }

} // namespace Engine
