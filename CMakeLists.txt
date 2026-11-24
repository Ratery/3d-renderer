cmake_minimum_required(VERSION 3.20)
project(3d-renderer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/eigen)
add_subdirectory(external/SFML)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/core/Color.cpp
        src/core/Triangle.cpp
        src/resources/mesh/ObjLoader.cpp
        src/resources/texture/Texture.cpp
        src/resources/texture/TextureLoader.cpp
        src/rendering/Frame.cpp
        src/rendering/Renderer.cpp
        src/rendering/pipeline/ClipPolygon.cpp
        src/rendering/material/Material.cpp
        src/rendering/shading/PhongShader.cpp
        src/rendering/lighting/AmbientLight.cpp
        src/rendering/lighting/DirectionalLight.cpp
        src/scene/Camera.cpp
        src/scene/Scene.cpp
        src/scene/Object.cpp
        src/exceptions/Except.cpp
        src/application/View.cpp
        src/application/Application.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/external/stb
)

find_package(OpenMP REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
        eigen
        SFML::Graphics
        SFML::Window
        SFML::System
        OpenMP::OpenMP_CXX
)

set(WARNINGS
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_compile_options(${PROJECT_NAME} PRIVATE
        ${WARNINGS}
        $<$<CONFIG:Debug>:-O0 -g>
        $<$<CONFIG:Release>:-O3 -march=native -ffast-math -flto>
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
