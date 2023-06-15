#include "Engine/LowAPI/Input/Input.h"
#include "GLFW/glfw3.h"

namespace Engine {
    Ref<Window> Input::m_window;

    bool Input::IsMouseButtonPress(MouseButtonCode button) {
        GLFWwindow* window = static_cast<GLFWwindow*>(m_window->GetNativeWindow());
        return static_cast<bool>(glfwGetMouseButton(window, static_cast<int>(button)));
    }

    bool Input::IsKeyPress(KeyCode key_code) {
        GLFWwindow* window = static_cast<GLFWwindow*>(m_window->GetNativeWindow());
        return glfwGetKey(window, static_cast<int>(key_code));
    }

    std::pair<uint32_t, uint32_t> Input::GetMousePos() {
        GLFWwindow* window = static_cast<GLFWwindow*>(m_window->GetNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return {x, y};
    }
} // namespace Engine
