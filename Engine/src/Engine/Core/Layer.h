#pragma once

#include "Engine/Event/WindowEvents.h"
#include <string>

namespace Engine {
    /**
     * The core user of engine functionality
     */
    class Layer {
    public:
        Layer(const std::string& name) : m_name{name} {}

        virtual ~Layer() = default;

        virtual void OnAttach(WindowEvents& events) {}

        virtual void OnDetach(WindowEvents& events) {}

        virtual void OnUpdate() {}

    private:
        std::string m_name;
    };
} // namespace Engine
