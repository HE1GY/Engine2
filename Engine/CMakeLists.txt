#variables
set(ENGINE_NAME "Engine")
set(ENGINE_SRC
        "src/Engine/Core/Application.cpp"
        "src/Engine/Core/Application.h"
        "src/Engine/Log/Log.cpp"
        "src/Engine/Log/Log.h"
        "src/Engine/Event/Event.h"
        "src/Engine/Event/WindowEventsPool.h"
        "src/Engine/LowAPI/Window.h"
        "src/Platform/Windows/WindowsWindow.h"
        "src/Platform/Windows/WindowsWindow.cpp"
        "src/Engine/Core/Ptrs.h"
        "src/Platform/OpenGL/OpenGLContext.h"
        "src/Platform/OpenGL/OpenGLContext.cpp")

#target
add_library(${ENGINE_NAME} STATIC ${ENGINE_SRC})
target_include_directories(${ENGINE_NAME} PUBLIC include src)

#link externals
target_link_libraries(${ENGINE_NAME} PUBLIC spdlog::spdlog)
target_link_libraries(${ENGINE_NAME} PUBLIC glfw)
target_link_libraries(${ENGINE_NAME} PUBLIC glad)
