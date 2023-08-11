#pragma once

#include "EnemyLogic.h"
#include "Engine/Engine.h"

namespace Game {
    using namespace Engine;
    class SpawnerScript : public CGameLogic::ILogic {
    public:
        SpawnerScript(Coordinator& coord, std::pair<int, int> window_prop, Ref<Texture> texture)
            : m_coord{coord}, m_window_prop{window_prop}, m_texture{texture} {
            std::srand(time(nullptr));
        }

        void RegisterScript(
            CGameLogic::Script& on_create, CGameLogic::Script& on_update, CGameLogic::Script& on_destroy) override {
            on_update = [this]() { OnUpdate(); };
        }

    private:
        void SpawnEnemy() {
            Vector2 pos{float(std::rand() % (int) (m_window_prop.first - 10) + 10), // radius
                float(std::rand() % (int) (m_window_prop.second - 10) + 10)};

            Entity enemy  = m_coord.CreateEntity();
            auto enemy_s  = std::make_shared<EnemyLogic>(enemy, m_coord, m_window_prop);
            auto& e_logic = m_coord.AddComponent<CGameLogic>(enemy);
            e_logic.SetScript(enemy_s);

            auto& transform    = m_coord.GetComponent<CTransform>(enemy);
            transform.position = {pos, 0};

            auto& rendC   = m_coord.GetComponent<CSpriteRenderer>(enemy);
            rendC.color   = GetRandomColor();
            rendC.texture = m_texture;

            auto& moveC     = m_coord.GetComponent<CMove>(enemy);
            moveC.direction = Vector3{float(std::rand() % m_window_prop.first - m_window_prop.first / 2.0),
                float(std::rand() % m_window_prop.second - m_window_prop.second / 2.0), 0.0f};
        }

        Vector4 GetRandomColor() {
            return glm::vec4{static_cast<float>(std::rand() % 255) / 255.0f,
                static_cast<float>(std::rand() % 255) / 255.0f, static_cast<float>(std::rand() % 255) / 255.0f, 1.0f};
        }

        void OnUpdate() {
            if (m_current_time <= 0) {
                SpawnEnemy();
                m_current_time = m_spawn_time;
            } else {
                m_current_time -= Time::s_delta_time;
            }
        }

    private:
        float m_current_time{};
        float m_spawn_time{3.0f};
        std::pair<int, int> m_window_prop;
        Coordinator& m_coord;
        Ref<Texture> m_texture;
    };
} // namespace Game
