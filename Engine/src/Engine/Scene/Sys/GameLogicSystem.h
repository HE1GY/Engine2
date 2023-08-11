#pragma once

#include "Engine/ECS/Coordinator.h"
namespace Engine {

    class GameLogicSystem : public System {
    public:
        GameLogicSystem(Coordinator& coord) : m_coord{coord} {
        }

        void Update();

    private:
        Coordinator& m_coord;
    };


} // namespace Engine
