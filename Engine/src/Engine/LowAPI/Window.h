#pragma once

#include "Engine/Event/WindowEvents.h"
#include <Engine/Core/Ptrs.h>
#include <string>


namespace Engine {
    /**
     * API for window interaction
     */
    class Window {
    public:
        struct WindowsProps {
            WindowsProps(uint32_t width = 1600, uint32_t height = 900, const std::string& title = "Engine")
                : width{width}, height{height}, title{title} {}

            uint32_t width, height;
            std::string title;
        };

        /**
                 * Main way of creating the window
                 * @param prop
                 * @return

         */
        static Ref<Window> Create(const WindowsProps& prop = WindowsProps());

        Window() = default;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual void SetEventCallbacks(const WindowEvents* fun) = 0;

        virtual void* GetNativeWindow() = 0;

        virtual void SetVSync(bool on) = 0;

        virtual bool GetVSync() const = 0;

        virtual float GetCurrentTime() = 0;

        virtual uint32_t GetWidth() = 0;

        virtual uint32_t GetHeight() = 0;
    };

} // namespace Engine
