#pragma once


#include "Components.h"
#include "System.h"
#include <functional>


namespace Engine {
    class Coordinator {
    public:
        void Init() {
            m_component_manager = std::make_unique<ComponentManager>();
            m_entity_manager    = std::make_unique<EntityManager>();
            m_system_manager    = std::make_unique<SystemManager>();
        }

        Entity CreateEntity() {
            return m_entity_manager->CreateEntity();
        }

        void DestroyEntity(Entity entity) {
            m_destroy_entities.insert(entity);
        }

        template <typename T>
        void RegisterComponent() {
            m_component_manager->RegisterComponent<T>();
        }

        template <typename T>
        T& AddComponent(Entity entity) {
            T& component = m_component_manager->AddComponent<T>(entity);

            auto signature = m_entity_manager->GetSignature(entity);
            signature.set(m_component_manager->GetComponentID<T>(), true);
            m_entity_manager->SetSignature(entity, signature);

            m_updated_entities.emplace_back(entity, signature);

            return component;
        }

        template <typename T>
        void RemoveComponent(Entity entity) {
            m_component_manager->RemoveComponent<T>(entity);

            auto signature = m_entity_manager->GetSignature(entity);
            signature.set(m_component_manager->GetComponentID<T>(), false);
            m_entity_manager->SetSignature(entity, signature);

            m_updated_entities.emplace_back(entity, signature);
        }

        template <typename T>
        T& GetComponent(Entity entity) {
            return m_component_manager->GetComponent<T>(entity);
        }

        template <typename T>
        bool HasComponent(Entity entity) {
            return m_entity_manager->GetSignature(entity).test(GetComponentID<T>());
        }

        template <typename T>
        ComponentID GetComponentID() {
            return m_component_manager->GetComponentID<T>();
        }

        template <typename T, typename... Args>
        std::shared_ptr<T> RegisterSystem(Args&&... args) {
            return m_system_manager->RegisterSystem<T>(std::forward<Args>(args)...);
        }

        template <typename T>
        void SetSystemSignature(Signature signature) {
            m_system_manager->SetSignature<T>(signature);
        }

        void Update() {
            std::for_each(m_updated_entities.begin(), m_updated_entities.end(),
                [&](auto& pair) { m_system_manager->EntitySignatureChanged(pair.first, pair.second); });

            std::for_each(m_destroy_entities.begin(), m_destroy_entities.end(), [&](auto& entity) {
                m_entity_manager->DestroyEntity(entity);
                m_component_manager->EntityDestroyed(entity);
                m_system_manager->EntityDestroyed(entity);
            });

            m_updated_entities.clear();
            m_destroy_entities.clear();
        }

    private:
        static std::unique_ptr<ComponentManager> m_component_manager;
        static std::unique_ptr<EntityManager> m_entity_manager;
        static std::unique_ptr<SystemManager> m_system_manager;

        static std::vector<std::pair<Entity, Signature>> m_updated_entities;
        static std::set<Entity> m_destroy_entities;
    };
} // namespace Engine
