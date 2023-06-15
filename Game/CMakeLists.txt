set(GAME_NAME "Game")
set(GAME_SRC "src/Game.cpp" "src/GameLayer.cpp")

add_executable(${GAME_NAME} ${GAME_SRC})
target_link_libraries(${GAME_NAME} PRIVATE Engine)


#Warnings
if (ENABLE_WARNINGS)
    target_set_warnings(${GAME_NAME} ${ENABLE_WARNINGS_AS_ERRORS})
endif ()