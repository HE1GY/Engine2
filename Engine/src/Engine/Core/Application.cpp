#include "Application.h"
#include "Engine/Log/Log.h"


namespace Engine
{
	Application::Application(const Window::WindowsProps& window_props)
	  : m_window{ Window::Create(window_props) }
	{
		m_window->SetVSync(true);
		m_window->SetEventCallbacks(&m_window_events);

		SubscribeEvents();
		/*m_window_events.onKeyTyped.AddCallback([](const auto& key)
		  {
			  CORE_INFO_LOG(static_cast<char>(key.key_code));
			  return false;
		  }
		);*/

	}


	void Application::Run()
	{
		while (m_is_running)
		{


			m_window->OnUpdate();
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


}