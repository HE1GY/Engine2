#pragma once

#include <GLFW/glfw3.h>
#include "Engine/LowAPI/Window.h"
#include "Engine/LowAPI/Renderer/GraphicContext.h"


namespace Engine
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowsProps& props);

		virtual ~WindowsWindow() override;


		virtual void OnUpdate() override;

		void* GetNativeWindow() override
		{
			return m_native_window;
		}

		virtual void SetEventCallbacks(const WindowEvents* callbacks) override
		{
			m_window_data.callbacks = callbacks;
		};

		virtual void SetVSync(bool on) override;

		virtual bool GetVSync() const
		{
			return m_is_vsync;
		};

		inline virtual unsigned int GetWidth() override
		{
			return m_window_data.props.width;
		};

		inline virtual unsigned int GetHeight() override
		{
			return m_window_data.props.height;
		};

		virtual float GetCurrentTime() override;

	private:
		void HookEvents();

	private:
		struct WindowData
		{
			WindowsProps props;
			const WindowEvents* callbacks;
		};

		GLFWwindow* m_native_window;
		GraphicContext* m_graphic_context;
		bool m_is_vsync;
		WindowData m_window_data;
	};
}