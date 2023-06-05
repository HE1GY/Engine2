#pragma once

#include "Engine/Event/WindowEventsPool.h"
#include "Ptrs.h"
#include "Engine/LowAPI/Window.h"
#include "Layer.h"
#include "LayerStack.h"

namespace Engine
{
	/**
	 * Core of engine
	 */
	class Application
	{
	public:
		Application(const Window::WindowsProps& window_props);

		virtual ~Application() = default;

		void Run();

	protected:
		void PushLayer(Ref<Layer> layer);

		void PushOverlayLayer(Ref<Layer> layer);

		void RemoveLayer(Ref<Layer> layer);

	private:
		void SubscribeEvents();

		bool OnWindowClosed(const WindowClosed& wc);

		bool OnWindowsResized(const WindowResized& wr);

	private:
		bool m_is_running{ true };
		WindowEvents m_window_events;
		Ref<Window> m_window;
		LayerStack m_layer_stack;
	};
}