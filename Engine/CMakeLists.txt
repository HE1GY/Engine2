#variables
set(ENGIN_NAME "Engine")
set(ENGINE_SRC
        "src/Core/Application.cpp"
        "src/Core/Application.h"
        "src/Log/Log.cpp"
        "src/Log/Log.h"
        "src/Event/Event.h"
        "src/Event/Event.cpp "
        "src/Event/WindowEventsPool.h")

#target
add_library(${ENGIN_NAME} STATIC ${ENGINE_SRC})
target_include_directories(Engine PUBLIC include src)


#link externals
target_link_libraries(${ENGIN_NAME} PUBLIC spdlog::spdlog)