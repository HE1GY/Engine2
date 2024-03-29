#include "GameLayer.h"
#include <Engine/Engine.h>
#include <Engine/EntryPoint.h>

namespace Game {
    /**
     * Main custom application
     */
    class Game : public Engine::Application {
    public:
        Game() : Engine::Application({800, 800, "Game"}) {
            PushLayer(Engine::CreateRef<GameLayer>("GameLayer"));
        }

        ~Game() override = default;
    };
} // namespace Game

/**
 * Method substitutes custom app fo Engine framework
 * @return custom app
 */
Engine::Application* CreateApplication() {
    return new Game::Game();
}
