#pragma once

#include "Defines.h"
#include "Entity.h"
#include <bitset>
#include <cassert>
#include <iostream>
#include <memory>
#include <set>
#include <unordered_map>

namespace Engine {
    // For informing that entity destroyed all arrays
    class IComponentArray {
    public:
        virtual ~IComponentArray()                  = default;
        virtual void EntityDestroyed(Entity entity) = 0;
    };

    template <typename T>
    class ComponentArray : public IComponentArray {
    public:
        T& InsertComponent(Entity entity) {
            assert(m_entity_2_index_map.find(entity) == m_entity_2_index_map.end()
                   && "Component added to same entity more than once.");

            size_t insert_index{};
            if (!m_insertion_indices.empty()) {
                insert_index = *m_insertion_indices.begin();
                m_insertion_indices.erase(insert_index);
            } else {
                insert_index = m_next_insertion_index++;
            }
            m_entity_2_index_map[entity] = insert_index;

            return m_components[insert_index];
        }

        void RemoveData(Entity entity) {
            assert(
                m_entity_2_index_map.find(entity) != m_entity_2_index_map.end() && "Removing non-existent component.");

            size_t remove_index = m_entity_2_index_map[entity];

            m_insertion_indices.insert(remove_index);
            m_components[remove_index] = {};
            m_entity_2_index_map.erase(entity);
        }

        T& GetData(Entity entity) {
            assert(m_entity_2_index_map.find(entity) != m_entity_2_index_map.end()
                   && "Retrieving non-existent component.");
            return m_components[m_entity_2_index_map[entity]];
        }

        void EntityDestroyed(Entity entity) override {
            if (m_entity_2_index_map.find(entity) != m_entity_2_index_map.end()) {
                RemoveData(entity);
            }
        }

    private:
        std::array<T, k_max_entity> m_components;

        std::unordered_map<Entity, size_t> m_entity_2_index_map;
        std::set<size_t> m_insertion_indices{};
        size_t m_next_insertion_index{};
    };

    class ComponentManager {
    public:
        template <typename T>
        void RegisterComponent() {
            std::string_view type_name = typeid(T).name();

            assert(m_components_ID.find(type_name) == m_components_ID.end()
                   && "Registering component type more than once.");

            m_components_ID.insert({type_name, m_component_id_counter});
            m_components_collections.insert({type_name, std::make_shared<ComponentArray<T>>()});
            ++m_component_id_counter;
        }

        template <typename T>
        ComponentID GetComponentID() {
            std::string_view typeName = typeid(T).name();
            assert(m_components_ID.find(typeName) != m_components_ID.end() && "Component not registered before use.");
            return m_components_ID[typeName];
        }

        template <typename T>
        T& AddComponent(Entity entity) {
            return GetComponentArray<T>()->InsertComponent(entity);
        }

        template <typename T>
        void RemoveComponent(Entity entity) {
            GetComponentArray<T>()->RemoveData(entity);
        }

        template <typename T>
        T& GetComponent(Entity entity) {
            return GetComponentArray<T>()->GetData(entity);
        }

        void EntityDestroyed(Entity entity) {
            for (auto const& pair : m_components_collections) {
                pair.second->EntityDestroyed(entity);
            }
        }

    private:
        template <typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray() {
            std::string_view typeName = typeid(T).name();
            assert(m_components_ID.find(typeName) != m_components_ID.end() && "Component not registered before use.");
            return std::static_pointer_cast<ComponentArray<T>>(m_components_collections[typeName]);
        }

    private:
        std::unordered_map<std::string_view, ComponentID> m_components_ID{};
        std::unordered_map<std::string_view, std::shared_ptr<IComponentArray>> m_components_collections{};
        ComponentID m_component_id_counter{};
    };
} // namespace Engine
