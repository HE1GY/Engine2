#pragma once

#include "Event/WindowEventsPool.h"

namespace Engine
{
	/**
	 * Core app which has main loop
	 */
	class Application
	{
	public:
		Application();

		virtual ~Application() = default;

		void Run();

	private:
		EventsPool m_window_events;
	};
}