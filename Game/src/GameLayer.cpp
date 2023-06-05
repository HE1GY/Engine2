#include "GameLayer.h"
#include "Engine/Engine.h"

namespace Game
{
	void GameLayer::OnAttach(Engine::WindowEvents& events)
	{
		events.onKeyTyped.AddCallback([](auto& event)
		{
			TRACE_LOG("In game use {0}", Engine::Time::s_delta_time);
			return false;
		});
	}

	void GameLayer::OnDetach(Engine::WindowEvents& events)
	{

	}

	void GameLayer::OnUpdate()
	{

		/*if (Engine::Input::IsKeyPress(Engine::KeyCode::D))
		{
			INFO_LOG(">>");
		}
		else if (Engine::Input::IsKeyPress(Engine::KeyCode::A))
		{
			INFO_LOG("<<");
		}*/
	}
}