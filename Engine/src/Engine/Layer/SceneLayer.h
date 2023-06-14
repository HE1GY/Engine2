#pragma once


#include "Engine/Core/Layer.h"
#include "Engine/LowAPI/Renderer/VertexArray.h"
#include "Engine/LowAPI/Renderer/Shader.h"

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

	private:
		Ref<VertexArray> m_vao;
		Ref<Shader> m_shader;
	};
}