#pragma once

#include "Engine/Event/WindowEventsPool.h"
#include "Ptrs.h"
#include "Engine/LowAPI/Window.h"

namespace Engine
{
	/**
	 * Core app which has main loop
	 */
	class Application
	{
	public:
		Application(const Window::WindowsProps& window_props);

		virtual ~Application() = default;

		void Run();

	private:
		void SubscribeEvents();

		bool OnWindowClosed(const WindowClosed& wc);

		bool OnWindowsResized(const WindowResized& wr);

	private:
		bool m_is_running{ true };
		EventsPool m_window_events;
		Ref<Window> m_window;
	};
}