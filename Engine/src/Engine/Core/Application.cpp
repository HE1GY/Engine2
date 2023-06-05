#include "Application.h"
#include "Engine/Log/Log.h"
#include "Engine/LowAPI/Input/Input.h"
#include "Time.h"
#include "Engine/Layer/SceneLayer.h"


namespace Engine
{
	Application::Application(const Window::WindowsProps& window_props)
	  : m_window{ Window::Create(window_props) }
	{
		m_window->SetVSync(true);
		m_window->SetEventCallbacks(&m_window_events);

		Input::Init(m_window);

		PushLayer(CreateRef<SceneLayer>("SceneLayer"));
	}


	void Application::Run()
	{
		//in run because to subscribe on events game layers
		SubscribeEvents();

		float last_frame_time = m_window->GetCurrentTime();
		while (m_is_running)
		{
			Time::s_delta_time = m_window->GetCurrentTime() - last_frame_time;
			last_frame_time = m_window->GetCurrentTime();

			for (const auto& layer: m_layer_stack)
			{
				layer->OnUpdate();
			}
			m_window->OnUpdate();

			Time::s_delta_time = m_window->GetCurrentTime();
		}
	}

	void Application::SubscribeEvents()
	{
		m_window_events.onWindowClosed.AddCallback(SUB_MEM(OnWindowClosed));
		m_window_events.onWindowResized.AddCallback(SUB_MEM(OnWindowsResized));
	}

	bool Application::OnWindowClosed(const WindowClosed& wc)
	{
		m_is_running = false;
		return false;
	}

	bool Application::OnWindowsResized(const WindowResized& wr)
	{
		//CORE_TRACE_LOG("{0} , {1}", wr.height, wr.width);
		return false;
	}

	void Application::PushLayer(Ref<Layer> layer)
	{
		layer->OnAttach(m_window_events);
		m_layer_stack.Push(layer);
	}

	void Application::PushOverlayLayer(Ref<Layer> layer)
	{
		layer->OnAttach(m_window_events);
		m_layer_stack.PushOverlay(layer);
	}

	void Application::RemoveLayer(Ref<Layer> layer)
	{
		layer->OnDetach(m_window_events);
		m_layer_stack.Remove(layer);
	}
}