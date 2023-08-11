#pragma once

#include "Engine/ECS/Coordinator.h"
#include "Engine/ECS/System.h"
#include "Engine/Event/WindowEvents.h"


namespace Engine {
    class Renderer2DSystem : public System {
    public:
        Renderer2DSystem(Coordinator& coord);

        void Update();

        void OnWindowResize(const WindowResized& wr);

    private:
        Coordinator& m_coord;
        int m_window_width;
        int m_window_height;
    };
} // namespace Engine
