#pragma once

#include "Entity.h"
#include <memory>
#include <set>
namespace Engine {
    class System {
    public:
        // with the same signature as in the system
        std::set<Entity> m_filtered_entities;
    };

    class SystemManager {
    public:
        template <typename T, typename... Args>
        std::shared_ptr<T> RegisterSystem(Args&&... args) {
            std::string_view typeName = typeid(T).name();

            assert(m_systems.find(typeName) == m_systems.end() && "Registering system more than once.");

            auto system = std::make_shared<T>(args...);
            m_systems.insert({typeName, system});
            return system;
        }

        template <typename T>
        void SetSignature(Signature signature) {
            std::string_view typeName = typeid(T).name();

            assert(m_systems.find(typeName) != m_systems.end() && "System used before registered.");
            m_signatures.insert({typeName, signature});
        }

        void EntityDestroyed(Entity entity) {
            for (auto const& pair : m_systems) {
                pair.second->m_filtered_entities.erase(entity);
            }
        }

        void EntitySignatureChanged(Entity entity, Signature entity_signature) {
            for (auto const& pair : m_systems) {
                auto const& type             = pair.first;
                auto const& system           = pair.second;
                auto const& system_signature = m_signatures[type];

                if ((entity_signature & system_signature) == system_signature) {
                    system->m_filtered_entities.insert(entity);
                } else {
                    system->m_filtered_entities.erase(entity);
                }
            }
        }

    private:
        std::unordered_map<std::string_view, Signature> m_signatures{};
        std::unordered_map<std::string_view, std::shared_ptr<System>> m_systems{};
    };
} // namespace Engine
