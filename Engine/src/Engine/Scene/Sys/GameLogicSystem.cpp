#include "GameLogicSystem.h"

#include "Engine/Scene/Components.h"

namespace Engine {
    void GameLogicSystem::Update() {
        for (auto& e : m_filtered_entities) {
            auto& game_logic = m_coord.GetComponent<CGameLogic>(e);
            game_logic.on_update();
        }
    }
} // namespace Engine
