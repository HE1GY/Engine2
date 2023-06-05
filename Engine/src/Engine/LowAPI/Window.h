#pragma once

#include <string>
#include "Engine/Event/WindowEventsPool.h"
#include <Engine/Core/Ptrs.h>


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

		static Ref<Window> Create(const WindowsProps& prop = WindowsProps());

		Window() = default;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual void SetEventCallbacks(const EventsPool* fun) = 0;

		virtual void* GetNativeWindow() = 0;

		virtual void SetVSync(bool on) = 0;

		virtual bool GetVSync() const = 0;

		virtual float GetCurrentTime() = 0;

		virtual uint32_t GetWidth() = 0;

		virtual uint32_t GetHeight() = 0;

	};

}