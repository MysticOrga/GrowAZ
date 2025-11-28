# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.10)

# Définition du projet
project(GrowAZ VERSION 1.0 LANGUAGES CXX)

# Spécifier la norme C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Raylib QUIET)

if(NOT Raylib_FOUND)
    message(STATUS "Raylib non trouvée. Téléchargement depuis GitHub...")
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
    )
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
else()
    message(STATUS "Raylib trouvée sur le système : ${RAYLIB_LIBRARIES}")
endif()

file(GLOB_RECURSE ALL_SOURCES "src/*.cpp")

add_executable(GrowAZ ${ALL_SOURCES})

target_include_directories(GrowAZ PUBLIC src)

target_link_libraries(GrowAZ PRIVATE raylib)
