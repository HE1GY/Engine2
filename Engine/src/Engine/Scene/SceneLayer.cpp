#include "SceneLayer.h"

#include "Components.h"
#include "Engine/ECS/Coordinator.h"
#include "Engine/LowAPI/Input/Input.h"
#include "Engine/Scene/Sys/GameLogicSystem.h"
#include "Engine/Scene/Sys/Renderer2DSystem.h"


namespace Engine {
    Coordinator coordinator{};

    void SceneLayer::OnAttach(WindowEvents& events) {
        coordinator.Init();

        coordinator.RegisterComponent<CTransform>();
        coordinator.RegisterComponent<CSpriteRenderer>();
        coordinator.RegisterComponent<CMove>();
        coordinator.RegisterComponent<CGameLogic>();
        coordinator.RegisterComponent<CCircleCollider>();

        m_renderer_sys = coordinator.RegisterSystem<Renderer2DSystem>(coordinator);
        {
            Signature signature;
            signature.set(coordinator.GetComponentID<CTransform>());

            signature.set(coordinator.GetComponentID<CSpriteRenderer>());

            coordinator.SetSystemSignature<Renderer2DSystem>(signature);
        }

        events.onWindowResized.AddCallback([this](auto& wc) { m_renderer_sys->OnWindowResize(wc); });

        m_move_sys = coordinator.RegisterSystem<MoveSystem>(coordinator);
        {
            Signature signature;

            signature.set(coordinator.GetComponentID<CTransform>());

            signature.set(coordinator.GetComponentID<CMove>());
            coordinator.SetSystemSignature<MoveSystem>(signature);
        }

        m_game_logic_sys = coordinator.RegisterSystem<GameLogicSystem>(coordinator);
        {
            Signature signature;
            signature.set(coordinator.GetComponentID<CGameLogic>());
            coordinator.SetSystemSignature<GameLogicSystem>(signature);
        }
        m_collision_sys = coordinator.RegisterSystem<CollisionSystem>(coordinator);
        {
            Signature signature;
            signature.set(coordinator.GetComponentID<CCircleCollider>());
            signature.set(coordinator.GetComponentID<CTransform>());
            coordinator.SetSystemSignature<CollisionSystem>(signature);
        }

        enum Layer {
            Player = 0,
            Enemy,
            SEnemy,
            Bullet,
        };
        m_collision_sys->SetLayerCollision(Layer::Player, Layer::Enemy);
        m_collision_sys->SetLayerCollision(Layer::Bullet, Layer::Enemy);
        // m_collision_sys->SetLayerCollision(Layer::Enemy, Layer::Enemy);
        m_collision_sys->SetLayerCollision(Layer::SEnemy, Layer::Player);
        m_collision_sys->SetLayerCollision(Layer::SEnemy, Layer::Bullet);
    }

    void SceneLayer::OnDetach(WindowEvents& events) {
    }

    void SceneLayer::OnUpdate() {

        coordinator.Update();
        m_game_logic_sys->Update();
        m_move_sys->Update();
        m_collision_sys->Update();
        m_renderer_sys->Update();
    }

} // namespace Engine
