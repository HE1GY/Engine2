set(GAME_SRC "src/Game.cpp" "src/GameLayer.cpp")

add_executable(Game ${GAME_SRC})
target_link_libraries(Game PRIVATE Engine)