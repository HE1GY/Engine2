cmake_minimum_required(VERSION 3.16)

project("Engine" VERSION 1.0.0 LANGUAGES C CXX)

# Global CMake variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#for cmake scripts
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

#dependencies
include(CPM)
cpmaddpackage("gh:gabime/spdlog#v1.11.0")
cpmaddpackage("gh:glfw/glfw#3.3.8")
cpmaddpackage("gh:HE1GY/glad#v1.0.1")
cpmaddpackage("gh:g-truc/glm#0.9.9.8")


#projects modules
add_subdirectory(Engine)
add_subdirectory(Game)


