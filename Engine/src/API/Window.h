#pragma once

#include <string>
#include <functional>


namespace Engine
{
	class Window
	{
	public:
		struct WindowsProps
		{
			WindowsProps(uint32_t width = 1600, uint32_t height = 900, const std::string& title = "Engine")
			  : width{ width }, height{ height }, title{ title }
			{
			}

			uint32_t width, height;
			std::string title;
		};

		using EventCallbackFn = std::function<void(const Event&)>;


		static Window* CreateWindow(const WindowsProps& prop = WindowsProps());

		Window() = default;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual void SetEventCallback(const EventCallbackFn& fun) = 0;

		virtual void* GetNativeWindow() = 0;

		virtual void SetVSync(bool on) = 0;

		virtual bool GetVSync() const = 0;

		virtual float GetCurrentTime() = 0;

		virtual uint32_t GetWidth() = 0;

		virtual uint32_t GetHeight() = 0;

	};

}