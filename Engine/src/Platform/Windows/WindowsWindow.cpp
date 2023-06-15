#include "WindowsWindow.h"

#include "Engine/Core/Ptrs.h"
#include "Engine/Log/Log.h"
#include "Engine/LowAPI/Window.h"
#include "Platform/OpenGL/OpenGLContext.h"


namespace Engine {
    /**
     * Callback for glfw errors
     * @param error code
     * @param description
     */
    static void GLFWErrorCallback(int error, const char* description) {
        CORE_ERROR_LOG("GLFW Error ({0}): {1}", error, description);
    }

    /**
         * Low level Window API implementation
         * @param prop  windows prop
         * @return created
     * window

     */
    Ref<Window> Window::Create(const Window::WindowsProps& prop) {
        return CreateRef<WindowsWindow>(prop);
    }


    WindowsWindow::WindowsWindow(const Window::WindowsProps& props) : m_window_data{props} {
        int32_t valid = glfwInit();
        CORE_ASSERT_LOG(valid, "Failed to init glfw");

        m_native_window = glfwCreateWindow(props.width, props.height, props.title.c_str(), NULL, NULL);
        CORE_ASSERT_LOG(m_native_window, "Failed to create  glfw window");

        glfwSetErrorCallback(GLFWErrorCallback);

        m_graphic_context = new OpenGLContext(m_native_window);

        glfwSetWindowUserPointer(m_native_window, &m_window_data);

        HookEvents();
    }

    WindowsWindow::~WindowsWindow() {
        delete m_graphic_context;
        glfwTerminate();
    }

    void WindowsWindow::HookEvents() {
        // Event handling
        glfwSetKeyCallback(m_native_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);

            if (action == GLFW_PRESS) {
                data->callbacks->onKeyPress.Invoke({key, 0});
            } else if (action == GLFW_RELEASE) {
                data->callbacks->onKeyReleased.Invoke({key});
            } else if (action == GLFW_REPEAT) {
                data->callbacks->onKeyPress.Invoke({key, 1});
            }
        });
        glfwSetCharCallback(m_native_window, [](GLFWwindow* window, unsigned int codepoint) {
            WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);

            data->callbacks->onKeyTyped.Invoke({static_cast<uint32_t>(codepoint)});
        });

        glfwSetWindowCloseCallback(m_native_window, [](GLFWwindow* window) {
            WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);

            data->callbacks->onWindowClosed.Invoke();
        });

        glfwSetWindowSizeCallback(m_native_window, [](GLFWwindow* window, int width, int height) {
            WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);

            data->props.width  = width;
            data->props.height = height;

            data->callbacks->onWindowResized.Invoke({width, height});
        });

        glfwSetMouseButtonCallback(m_native_window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);

            if (action == GLFW_PRESS) {
                data->callbacks->onMouseButtonPressed.Invoke({button});
            } else if (action == GLFW_RELEASE) {
                data->callbacks->onMouseButtonReleased.Invoke({button});
            }
        });

        glfwSetScrollCallback(m_native_window, [](GLFWwindow* window, double xoffset, double yoffset) {
            WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);

            data->callbacks->onMouseScrolled.Invoke({static_cast<int32_t>(xoffset), static_cast<int32_t>(yoffset)});
        });

        glfwSetCursorPosCallback(m_native_window, [](GLFWwindow* window, double xpos, double ypos) {
            WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
            data->callbacks->onMouseMoved.Invoke({static_cast<int32_t>(xpos), static_cast<int32_t>(ypos)});
        });
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        m_graphic_context->SwapBuffer();
    }

    void WindowsWindow::SetVSync(bool on) {
        m_is_vsync = on;
        glfwSwapInterval(m_is_vsync ? 1 : 0);
    }

    float WindowsWindow::GetCurrentTime() {
        return static_cast<float>(glfwGetTime());
    }
} // namespace Engine
