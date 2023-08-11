#include "Coordinator.h"
namespace Engine {
    std::unique_ptr<ComponentManager> Coordinator::m_component_manager;
    std::unique_ptr<EntityManager> Coordinator::m_entity_manager;
    std::unique_ptr<SystemManager> Coordinator::m_system_manager;

    std::vector<std::pair<Entity, Signature>> Coordinator::m_updated_entities;
    std::set<Entity> Coordinator::m_destroy_entities;
} // namespace Engine
