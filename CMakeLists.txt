cmake_minimum_required(VERSION 3.16)

project("Engine" VERSION 1.0.0 LANGUAGES C CXX)

# Global CMake variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#for cmake scripts
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

#dependencies
include(CPM)
cpmaddpackage("gh:gabime/spdlog#v1.11.0")


#projects modules
add_subdirectory(Engine)
add_subdirectory(Game)


