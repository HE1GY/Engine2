#pragma once

#include <Engine/Core/Layer.h>

namespace Game
{
	class GameLayer : public Engine::Layer
	{
	public :
		GameLayer(const std::string& name)
		  : Layer{ name }
		{
		}

		~GameLayer() = default;

		virtual void OnAttach(Engine::WindowEvents& events) override;

		virtual void OnDetach(Engine::WindowEvents& events) override;

		virtual void OnUpdate() override;
	};
}