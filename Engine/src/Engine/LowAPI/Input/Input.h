#pragma once
#include "Engine/LowAPI/Window.h"
#include "InputCodes.h"
#include <utility>
namespace Engine {
    /**
     * Polling input
     */
    class Input {
    public:
        static void Init(Ref<Window>& window) {
            m_window = window;
        }
        static bool IsMouseButtonPress(MouseButtonCode button);
        static bool IsKeyPress(KeyCode key_code);
        static std::pair<uint32_t, uint32_t> GetMousePos();

    private:
        static Ref<Window> m_window;
    };
} // namespace Engine
