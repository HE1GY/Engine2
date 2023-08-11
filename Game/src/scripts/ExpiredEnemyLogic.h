#pragma once

#include "EnemyLogic.h"
#include "Time.h"

namespace Game {
    class ExpiredEnemyLogic : public EnemyLogic {
    public:
        ExpiredEnemyLogic(Entity entity, Coordinator& coord, std::pair<int, int> window_prop, float life_time)
            : EnemyLogic{entity, coord, window_prop}, m_life_time{life_time}, m_max_life_time{life_time} {
        }

        void RegisterScript(
            CGameLogic::Script& on_create, CGameLogic::Script& on_update, CGameLogic::Script& on_destroy) override {
            on_create  = [this]() { OnCreate(); };
            on_update  = [this]() { OnUpdate(); };
            on_destroy = [this]() { OnDestroy(); };
        }

    protected:
        void OnCreate() {
            m_coord.AddComponent<CSpriteRenderer>(m_entity);

            m_coord.AddComponent<CTransform>(m_entity);
            auto& move = m_coord.AddComponent<CMove>(m_entity);

            move.move_speed     = 150;
            move.rotation_speed = 70;

            auto& collider        = m_coord.AddComponent<CCircleCollider>(m_entity);
            collider.radius       = 10.0f;
            collider.layer        = 2;
            collider.on_collision = [this]() { OnCollision(); };
        }
        void OnUpdate() {
            EnemyLogic::OnUpdate();

            m_life_time -= Time::s_delta_time;
            if (m_life_time <= 0) {
                m_coord.DestroyEntity(m_entity);
                return;
            }

            float alpha = (m_life_time / m_max_life_time);

            CSpriteRenderer& cr = m_coord.GetComponent<CSpriteRenderer>(m_entity);
            cr.color.a          = alpha;
        }
        void OnDestroy() {
        }

        void OnCollision() {
            m_coord.DestroyEntity(m_entity);
        }

    private:
        float m_life_time{};
        float m_max_life_time{};
    };
} // namespace Game
