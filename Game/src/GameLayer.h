#pragma once

#include <Engine/Core/Layer.h>

namespace Game {
    class GameLayer : public Engine::Layer {
    public:
        explicit GameLayer(const std::string& name) : Layer{name} {}

        ~GameLayer() override = default;

        void OnAttach(Engine::WindowEvents& events) override;

        void OnDetach(Engine::WindowEvents& events) override;

        void OnUpdate() override;
    };
} // namespace Game
