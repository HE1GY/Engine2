#include "Application.h"

#include "Engine/LowAPI/Input/Input.h"
#include "Engine/LowAPI/Renderer/Renderer2D.h"
#include "Engine/LowAPI/Renderer/RendererCommand.h"
#include "Engine/Scene/SceneLayer.h"
#include "Time.h"


namespace Engine {
    Application::Application(const Window::WindowsProps& window_props) : m_window{Window::Create(window_props)} {
        m_window->SetVSync(true);
        m_window->SetEventCallbacks(&m_window_events);

        Input::Init(m_window);
        Renderer2D::Init(Renderer2D::API::OpenGL);

        m_scene_layer = CreateRef<SceneLayer>("SceneLayer");
        PushLayer(m_scene_layer);
    }

    void Application::Run() {
        // SubscribeEvents in run because to subscribe on events game layers
        SubscribeEvents();
        m_window_events.onWindowResized.Invoke({(int) m_window->GetWidth(), (int) m_window->GetHeight()}); // first
                                                                                                           // event

        float last_frame_time = m_window->GetCurrentTime();
        while (m_is_running) {
            Time::s_delta_time = m_window->GetCurrentTime() - last_frame_time;
            last_frame_time    = m_window->GetCurrentTime();

            for (const auto& layer : m_layer_stack) {
                layer->OnUpdate();
            }
            m_window->OnUpdate();

            Time::s_delta_time = m_window->GetCurrentTime();
        }
    }

    void Application::SubscribeEvents() {
        m_window_events.onWindowClosed.AddCallback(MEM_FN_NOARGS_TO_LMD(OnWindowClosed));
        m_window_events.onWindowResized.AddCallback(MEM_FN_TO_LMD(OnWindowsResized));
    }

    void Application::OnWindowClosed() {
        m_is_running = false;
    }

    void Application::OnWindowsResized(const WindowResized& wr) {
        RendererCommand::SetViewport(0, 0, wr.width, wr.height);
        Renderer2D::OnAspectRationChange(static_cast<float>(wr.width) / wr.height);
    }

    void Application::PushLayer(Ref<Layer> layer) {
        layer->OnAttach(m_window_events);
        m_layer_stack.Push(layer);
    }

    void Application::PushOverlayLayer(Ref<Layer> layer) {
        layer->OnAttach(m_window_events);
        m_layer_stack.PushOverlay(layer);
    }

    void Application::RemoveLayer(Ref<Layer> layer) {
        layer->OnDetach(m_window_events);
        m_layer_stack.Remove(layer);
    }
} // namespace Engine
