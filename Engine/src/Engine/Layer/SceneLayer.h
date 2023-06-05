#pragma once


#include "Engine/Core/Layer.h"

namespace Engine
{
	class SceneLayer : public Layer
	{
	public:
		SceneLayer(const std::string& name)
		  : Layer{ name }
		{
		}

		virtual ~SceneLayer() override = default;

		virtual void OnAttach(WindowEvents& events) override;

		virtual void OnDetach(WindowEvents& events) override;

		virtual void OnUpdate() override;

	};
}