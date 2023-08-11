#pragma once

#include "Engine/Engine.h"

namespace Game {
    using namespace Engine;
    class EnemyLogic : public CGameLogic::ILogic {
    public:
        EnemyLogic(Entity entity, Coordinator& coord, std::pair<int, int> window_prop)
            : m_entity{entity}, m_coord{coord}, m_window_prop{window_prop} {
        }

        void RegisterScript(
            CGameLogic::Script& on_create, CGameLogic::Script& on_update, CGameLogic::Script& on_destroy) override {
            on_create  = [this]() { OnCreate(); };
            on_update  = [this]() { OnUpdate(); };
            on_destroy = [this]() { OnDestroy(); };
        }

    protected:
        void OnCreate() {

            auto& spr    = m_coord.AddComponent<CSpriteRenderer>(m_entity);
            spr.priority = 0;

            auto& trans    = m_coord.AddComponent<CTransform>(m_entity);
            trans.position = {500, 400, 0};
            trans.scale    = {80, 80, 1};

            CMove& move = m_coord.AddComponent<CMove>(m_entity);
            {
                move.direction      = {1, 1, 0};
                move.move_speed     = 150;
                move.rotation_speed = 150;
            }

            CCircleCollider& circle_Col = m_coord.AddComponent<CCircleCollider>(m_entity);
            circle_Col.radius           = 32;
            circle_Col.layer            = 1;
            circle_Col.on_collision     = [this]() { OnCollision(); };
        }
        void OnUpdate() {
            auto& move     = m_coord.GetComponent<CMove>(m_entity);
            auto& transf   = m_coord.GetComponent<CTransform>(m_entity);
            auto& collider = m_coord.GetComponent<CCircleCollider>(m_entity);

            if ((transf.position.x + collider.radius > m_window_prop.first && move.direction.x > 0)
                || (transf.position.x - collider.radius < 0 && move.direction.x < 0)) {
                move.direction.x *= -1;
            }

            if ((transf.position.y + collider.radius > m_window_prop.second && move.direction.y > 0)
                || (transf.position.y - collider.radius < 0 && move.direction.y < 0)) {
                move.direction.y *= -1;
            }
        }
        void OnDestroy() {
        }

        void OnCollision();

    protected:
        Entity m_entity;
        Coordinator& m_coord;
        std::pair<int, int> m_window_prop;
    };
} // namespace Game
