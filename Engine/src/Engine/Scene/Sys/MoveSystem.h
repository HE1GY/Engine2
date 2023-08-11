#pragma once

#include "Engine/ECS/Coordinator.h"

namespace Engine {
    class MoveSystem : public System {
    public:
        MoveSystem(Coordinator& coord) : m_coord{coord} {
        }

        void Update();

    private:
        Coordinator& m_coord;
    };
} // namespace Engine
