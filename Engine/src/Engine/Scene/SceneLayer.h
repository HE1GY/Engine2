#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/Core/Ptrs.h"
#include "Engine/Scene/Sys/CollisionSystem.h"
#include "Engine/Scene/Sys/GameLogicSystem.h"
#include "Sys/MoveSystem.h"
#include "Sys/Renderer2DSystem.h"

namespace Engine {
    class SceneLayer : public Layer {
    public:
        explicit SceneLayer(const std::string& name) : Layer{name} {
        }

        ~SceneLayer() override = default;

        void OnAttach(WindowEvents& events) override;

        void OnDetach(WindowEvents& events) override;

        void OnUpdate() override;

    private:
        Ref<Renderer2DSystem> m_renderer_sys;
        Ref<MoveSystem> m_move_sys;
        Ref<GameLogicSystem> m_game_logic_sys;
        Ref<CollisionSystem> m_collision_sys;
    };
} // namespace Engine
