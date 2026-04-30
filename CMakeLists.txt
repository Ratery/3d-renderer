cmake_minimum_required(VERSION 3.20)
project(3d-renderer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(external/eigen)
add_subdirectory(external/SFML)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/core/Triangle.cpp
        src/core/Color.cpp
        src/scene/Camera.cpp
        src/scene/Scene.cpp
        src/scene/Object.cpp
        src/render/RenderVertex.h
        src/render/Frame.cpp
        src/render/Renderer.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} PRIVATE
        eigen
        SFML::Graphics
        SFML::Window
        SFML::System
)
