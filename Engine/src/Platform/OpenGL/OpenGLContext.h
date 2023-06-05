#pragma once

#include "Engine/LowAPI/Renderer/GraphicContext.h"

struct GLFWwindow;
namespace Engine
{
	class OpenGLContext : public GraphicContext
	{
	public:
		OpenGLContext(GLFWwindow* window_handler);

		virtual void SwapBuffer() override;

	private:
		GLFWwindow* m_window_handler;
	};
}