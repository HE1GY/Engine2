#include "GameLayer.h"

#include "Engine/Engine.h"
#include "scripts/EnemyLogic.h"
#include "scripts/PlayerLogic.h"
#include "scripts/SpawnerScript.h"


namespace Engine {
    extern Coordinator coordinator;
}

namespace Game {

    void GameLayer::OnAttach(Engine::WindowEvents& events) {

        auto player = coordinator.CreateEntity();

        auto player_script = std::make_shared<PlayerLogic>(player, coordinator);
        auto& logic        = coordinator.AddComponent<CGameLogic>(player);
        logic.SetScript(player_script);


        auto enemy        = coordinator.CreateEntity();
        auto enemy_script = std::make_shared<EnemyLogic>(enemy, coordinator, std::pair{800, 800}); // TODO
        auto& enemy_logic = coordinator.AddComponent<CGameLogic>(enemy);
        enemy_logic.SetScript(enemy_script);

        auto& enemy_sprite   = coordinator.GetComponent<CSpriteRenderer>(enemy);
        enemy_sprite.texture = Renderer2D::CreateTexture("Game/assets/classic-border-red-circle-free-png-x2X5ZG.png");
        enemy_sprite.color   = {0, 0, 1, 1};


        auto spawner        = coordinator.CreateEntity();
        auto& spawner_logic = coordinator.AddComponent<CGameLogic>(spawner);
        spawner_logic.SetScript(
            std::make_shared<SpawnerScript>(coordinator, std::pair{800, 800}, enemy_sprite.texture));
    }

    void GameLayer::OnDetach(Engine::WindowEvents& events) {
    }

    void GameLayer::OnUpdate() {
    }

} // namespace Game
