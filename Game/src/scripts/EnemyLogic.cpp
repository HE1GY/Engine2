
#include "EnemyLogic.h"

#include "ExpiredEnemyLogic.h"

namespace Game {
    void EnemyLogic::OnCollision() {
        const double PI = 3.14159265358979323846;

        auto& circle   = m_coord.GetComponent<CSpriteRenderer>(m_entity);
        auto& tranform = m_coord.GetComponent<CTransform>(m_entity);

        float degree_step = 360.0f / 6; // 6 side
        float radian_step = degree_step * (PI / 180);
        for (int i = 0; i < 6; ++i) {
            Vector2 dir = {(float) std::cos(radian_step * i), (float) std::sin(radian_step * i)};
            dir         = glm::normalize(dir);

            auto small_enemy = m_coord.CreateEntity();

            auto enemy_logic = std::make_shared<ExpiredEnemyLogic>(small_enemy, m_coord, m_window_prop, 1.0f);
            auto& logic      = m_coord.AddComponent<CGameLogic>(small_enemy);
            logic.SetScript(enemy_logic);

            auto& pos    = m_coord.GetComponent<CTransform>(small_enemy);
            pos.position = tranform.position;

            auto& move     = m_coord.GetComponent<CMove>(small_enemy);
            move.direction = {dir, 0};

            auto& rend    = m_coord.GetComponent<CSpriteRenderer>(small_enemy);
            rend.color    = circle.color;
            rend.priority = 0;
            rend.texture  = circle.texture;

            pos.scale = tranform.scale / 2.0f;
        }
        m_coord.DestroyEntity(m_entity);
    }
} // namespace Game
