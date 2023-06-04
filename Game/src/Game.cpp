#include <Engine.h>
#include <EntryPoint.h>


/**
 * Main custom application
 */
class Game : public Engine::Application
{
public:
	Game()
	{
		INFO_LOG("Start game");
		CORE_ASSERT_LOG(false, "Fuck");
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




