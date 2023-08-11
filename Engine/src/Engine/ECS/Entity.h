#pragma once

#include "Defines.h"
#include <array>
#include <cassert>
#include <cstdint>
#include <queue>

using Entity = std::uint32_t;

constexpr uint32_t k_max_entity{1000u};
namespace Engine {
    class EntityManager {
    public:
        EntityManager() {
            for (Entity entity{0}; entity < k_max_entity; ++entity) {
                m_available_entities.push(entity);
            }
        }

        Entity CreateEntity() {
            assert(m_living_entity < k_max_entity && "Too many entities in existence.");

            Entity id = m_available_entities.front();
            m_available_entities.pop();
            ++m_living_entity;

            return id;
        }

        void DestroyEntity(Entity entity) {
            assert(entity < k_max_entity && "Entity out of range.");

            m_signatures[entity].reset();
            m_available_entities.push(entity);
            --m_living_entity;
        }

        void SetSignature(Entity entity, Signature signature) {
            assert(entity < k_max_entity && "Entity out of range.");
            m_signatures[entity] = signature;
        }

        Signature GetSignature(Entity entity) {
            assert(entity < k_max_entity && "Entity out of range.");
            return m_signatures[entity];
        }

    private:
        std::queue<Entity> m_available_entities{};
        std::array<Signature, k_max_entity> m_signatures{};
        uint32_t m_living_entity{};
    };
} // namespace Engine
