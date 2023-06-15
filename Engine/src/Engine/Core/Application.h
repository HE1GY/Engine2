#pragma once

#include "Engine/Event/WindowEvents.h"
#include "Engine/LowAPI/Window.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Ptrs.h"

namespace Engine {
    /**
     * Core of engine
     */
    class Application {
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

        void OnWindowClosed();

        void OnWindowsResized(const WindowResized& wr);

    private:
        bool m_is_running{true};
        WindowEvents m_window_events;
        Ref<Window> m_window;
        LayerStack m_layer_stack;
    };
} // namespace Engine
