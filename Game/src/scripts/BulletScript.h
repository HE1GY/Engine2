#pragma once

#include "Engine/Engine.h"
#include <utility>

namespace Game {

    using namespace Engine;

    class BulletScript : public CGameLogic::ILogic {
    public:
        BulletScript(Entity e, Coordinator& c) : m_entity{e}, m_coord{c} {
        }

        void RegisterScript(
            CGameLogic::Script& on_create, CGameLogic::Script& on_update, CGameLogic::Script& on_destroy) override {
            on_create  = [this]() { OnCreate(); };
            on_update  = [this]() { OnUpdate(); };
            on_destroy = [this]() { OnDestroy(); };
        }

        Event<> collision;

    private:
        void OnCreate() {
            auto& bullet_m          = m_coord.AddComponent<CMove>(m_entity);
            bullet_m.rotation_speed = 150;
            bullet_m.move_speed     = 350;

            m_coord.AddComponent<CTransform>(m_entity);

            auto& spr    = m_coord.AddComponent<CSpriteRenderer>(m_entity);
            spr.priority = 1;

            auto& collider        = m_coord.AddComponent<CCircleCollider>(m_entity);
            collider.radius       = 15;
            collider.layer        = 3;
            collider.on_collision = [this]() { collision.Invoke(); };

            collision.AddCallback(MEM_FN_NOARGS_TO_LMD(OnCollision));
        }
        void OnUpdate() {
            m_life_time -= Time::s_delta_time;

            if (m_life_time <= 0) {
                m_coord.DestroyEntity(m_entity);
                return;
            }

            float alpha = m_life_time / m_max_life_time;

            CSpriteRenderer& cr = m_coord.GetComponent<CSpriteRenderer>(m_entity);
            cr.color.a          = alpha;
        }

        void OnCollision() {
            m_coord.DestroyEntity(m_entity);
        }
        void OnDestroy() {
        }

    private:
        Entity m_entity;
        Coordinator& m_coord;

        float m_max_life_time{1.5f};
        float m_life_time{m_max_life_time};
    };
} // namespace Game
