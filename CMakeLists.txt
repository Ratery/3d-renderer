cmake_minimum_required(VERSION 3.20)
project(3d-renderer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/eigen)
add_subdirectory(external/SFML)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/core/Triangle.cpp
        src/scene/Camera.cpp
        src/scene/Scene.cpp
        src/scene/Object.cpp
        src/render/ClipPolygon.cpp
        src/render/Frame.cpp
        src/render/Renderer.cpp
        src/lighting/Color.cpp
        src/lighting/Material.cpp
        src/lighting/AmbientLight.cpp
        src/lighting/DirectionalLight.cpp
        src/lighting/PhongShader.cpp
        src/loader/ObjLoader.cpp
        src/exceptions/Except.cpp
        src/application/View.cpp
        src/application/Application.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

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
        $<$<CONFIG:Release>:-O3 -march=native -ffast-math>
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
