#include <Engine/Engine.h>
#include <Engine/EntryPoint.h>


/**
 * Main custom application
 */
class Game : public Engine::Application
{
public:
	Game()
	  : Engine::Application({ 600, 400, "Game" })
	{
		INFO_LOG("Start game");
	}

	~Game() override = default;
};


/**
 * Method substitutes custom app fo Engine framework
 * @return custom app
 */
Engine::Application* CreateApplication()
{
	return new Game();
}




