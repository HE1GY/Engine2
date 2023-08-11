#variables
set(ENGINE_NAME "Engine")
set(ENGINE_SRC
        "src/Engine/Core/Application.cpp"
        "src/Engine/Core/Application.h"
        "src/Engine/Log/Log.cpp"
        "src/Engine/Log/Log.h"
        "src/Engine/Event/Event.h"
        "src/Engine/Event/WindowEvents.h"
        "src/Engine/LowAPI/Window.h"
        "src/Platform/Windows/WindowsWindow.h"
        "src/Platform/Windows/WindowsWindow.cpp"
        "src/Engine/Core/Ptrs.h"
        "src/Platform/OpenGL/OpenGLContext.h"
        "src/Platform/OpenGL/OpenGLContext.cpp"
        "src/Engine/Core/Layer.h"
        "src/Engine/Core/LayerStack.cpp"
        "src/Engine/Core/LayerStack.h"
        "src/Engine/LowAPI/Input/InputCodes.h"
        "src/Engine/LowAPI/Input/Input.h"
        "src/Platform/Windows/InputWindows.cpp"
        "src/Engine/Core/Time.h"
        "src/Engine/Scene/SceneLayer.cpp"
        "src/Engine/Scene/SceneLayer.h"
        "src/Engine/LowAPI/Renderer/Buffer.h"
        "src/Engine/LowAPI/Renderer/Renderer2D.cpp"
        "src/Engine/LowAPI/Renderer/Renderer2D.h"
        "src/Engine/LowAPI/Renderer/RendererCommand.h"
        "src/Engine/LowAPI/Renderer/Shader.h"
        "src/Engine/LowAPI/Renderer/VertexArray.h"
        "src/Platform/OpenGL/OpenGLBuffer.h"
        "src/Platform/OpenGL/OpenGLBuffer.cpp"
        "src/Platform/OpenGL/OpenGLVertexArray.h"
        "src/Platform/OpenGL/OpenGLVertexArray.cpp"
        "src/Platform/OpenGL/OpenGLCommand.cpp"
        "src/Platform/OpenGL/OpenGLShader.cpp"
        "src/Platform/OpenGL/OpenGLTexture.cpp"
        "src/Engine/LowAPI/Renderer/Texture.h"
        "src/Engine/LowAPI/Renderer/GraphicObjectFactory.h"
        "src/Platform/OpenGL/OpenGLObjectFactory.cpp"
        "src/Platform/OpenGL/OpenGLObjectFactory.h"
        "src/Engine/Utils/FileHandler.cpp"
        "src/Engine/Utils/FileHandler.h"
        "src/Engine/Utils/ImageLoader.cpp"
        "src/Engine/Utils/ImageLoader.h"
        "src/Engine/Scene/Components.h"
        "src/Engine/Scene/Components.h"
        "src/Engine/Math/Vector.cpp"
        "src/Engine/Math/Vector.h"
        "src/Engine/Math/Vector.h"
        "src/Engine/Math/Vector.cpp"
        "src/Engine/Math/Matrix.cpp"
        "src/Engine/Math/Matrix.h"
        "src/Engine/Math/Math.h"
        src/Engine/ECS/Components.h
        src/Engine/ECS/Coordinator.cpp
        src/Engine/ECS/Coordinator.h
        src/Engine/ECS/Entity.h
        src/Engine/ECS/System.h
        src/Engine/Scene/Sys/Renderer2DSystem.h
        src/Engine/Scene/Sys/Renderer2DSystem.cpp
        src/Engine/Scene/Sys/MoveSystem.h
        src/Engine/Scene/Sys/MoveSystem.cpp
        src/Engine/ECS/Defines.h
        src/Engine/Scene/Sys/GameLogicSystem.h
        src/Engine/Scene/Sys/GameLogicSystem.cpp
        src/Engine/Scene/Sys/CollisionSystem.cpp
        src/Engine/Scene/Sys/CollisionSystem.h)

#target
add_library(${ENGINE_NAME} STATIC ${ENGINE_SRC})
target_include_directories(${ENGINE_NAME} PUBLIC include src)

#link externals
target_link_libraries(${ENGINE_NAME} PUBLIC spdlog::spdlog)
target_link_libraries(${ENGINE_NAME} PUBLIC glfw)
target_link_libraries(${ENGINE_NAME} PUBLIC glad)
target_link_libraries(${ENGINE_NAME} PUBLIC glm::glm)
target_link_libraries(${ENGINE_NAME} PUBLIC stb_image)

#addition options
if (${ENABLE_WARNINGS})
    target_set_warnings(${ENGINE_NAME} ${ENABLE_WARNINGS_AS_ERRORS})
endif ()

if (${ENABLE_LTO})
    target_enable_lto(${ENGINE_NAME})
endif ()

if (${ENABLE_CLANG_TIDY})
    add_clang_tidy_msvc_to_target(${ENGINE_NAME})
endif ()
