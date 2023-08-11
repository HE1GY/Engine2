#pragma once

#include "Engine/ECS/Coordinator.h"
#include "Engine/ECS/System.h"
#include "Engine/Scene/Components.h"
namespace Engine {
    class CollisionSystem : public System {
    public:
        CollisionSystem(Coordinator& coord) : m_coord{coord}, m_collision_matrix(m_layer_count) {
        }

        void Update() {
            m_collided.clear();
            for (auto& e : m_filtered_entities) {
                auto& transform = m_coord.GetComponent<CTransform>(e);
                auto& collider  = m_coord.GetComponent<CCircleCollider>(e);
                for (auto& e2 : m_filtered_entities) {
                    if (e == e2) {
                        continue;
                    }
                    auto& transform2 = m_coord.GetComponent<CTransform>(e2);
                    auto& collider2  = m_coord.GetComponent<CCircleCollider>(e2);

                    if (CollidedLayer(collider.layer, collider2.layer) && m_collided.find(e) == m_collided.end()
                        && (glm::length(transform.position - transform2.position)
                            < collider.radius + collider2.radius)) {
                        if (collider.on_collision) {
                            collider.on_collision();
                        }
                        if (collider2.on_collision) {
                            collider2.on_collision();
                        }
                        m_collided.insert({e2, e});
                    }
                }
            }
        }

        void SetLayerCollision(uint32_t layer1, uint32_t layer2) {
            m_collision_matrix[layer1].set(layer2);
            m_collision_matrix[layer2].set(layer1);
        }

    private:
        bool CollidedLayer(uint32_t layer1, uint32_t layer2) {
            return m_collision_matrix[layer1].test(layer2);
        }

    private:
        static constexpr int32_t m_layer_count{32};


        Coordinator& m_coord;
        std::unordered_map<Entity, Entity> m_collided{};
        std::vector<std::bitset<m_layer_count>> m_collision_matrix;
    };
} // namespace Engine
