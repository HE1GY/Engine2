cmake_minimum_required(VERSION 3.16)

project("Engine" VERSION 1.0.0 LANGUAGES C CXX)

# Global CMake variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(ENABLE_WARNINGS "Enable warnings" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable warnings as errors" OFF)

option(ENABLE_SANITIZE_ADDR "Enable runtime address sanitizer" ON)
option(ENABLE_SANITIZE_UNDEF "Enable runtime undefined sanitizer" ON)

option(ENABLE_LTO "Enable link time optimization" ON)

option(ENABLE_CLANG_TIDY "Enable LLVM clang-tidy" ON)


#cmake scripts
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(CPM)
include(Docs)
include(ConfigSafeGuards)
include(Tools)

if (${ENABLE_WARNINGS})
    include(Warnings)
endif ()

if (${ENABLE_SANITIZE_ADDR} OR ${ENABLE_SANITIZE_UNDEF})
    include(Sanitizer)
endif ()

if (${ENABLE_LTO})
    include(LTO)
endif ()


#dependencies
cpmaddpackage("gh:gabime/spdlog#v1.11.0")
cpmaddpackage("gh:glfw/glfw#3.3.8")
cpmaddpackage("gh:HE1GY/glad#v1.0.1")
cpmaddpackage("gh:g-truc/glm#0.9.9.8")
cpmaddpackage("gh:HE1GY/stb_image#v1.0.0")

#projects modules
add_subdirectory(Engine)
add_subdirectory(Game)
