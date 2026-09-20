cmake_minimum_required(VERSION 3.28)

project(Application)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Application STATIC)

target_sources(Application PRIVATE

    "include/glm.hpp"
    "include/io.hpp"

    "include/application/application.hpp"
    "include/application/config.hpp"
    "include/application/context.hpp"
    "include/application/layer.hpp"
    "include/application/scene.hpp"
    "include/application/sdl.hpp"

    "include/graphics/buffer.hpp"
    "include/graphics/config.hpp"
    "include/graphics/context.hpp"
    "include/graphics/gpu_objects.hpp"
    "include/graphics/graphics.hpp"
    "include/graphics/image.hpp"
    "include/graphics/single_command_buffer.hpp"
    "include/graphics/slang_compiler.hpp"
    "include/graphics/vulkan_layer.hpp"
    "include/graphics/image_layout.hpp"
    "include/graphics/imgui_impl.hpp"
    "include/graphics/compute_shader.hpp"

    "include/player/camera.hpp"
    "include/player/camera_layer.hpp"

    "include/resources/allocator.hpp"
    "include/resources/assets.hpp"
    "include/resources/handle.hpp"
    "include/resources/material.hpp"
    "include/resources/mesh_imports.hpp"
    "include/resources/mesh.hpp"
    "include/resources/object_loader.hpp"
    "include/resources/primitive_meshes.hpp"
    "include/resources/stb_image.hpp"
    "include/resources/texture_imports.hpp"
)
target_include_directories(Application PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_precompile_headers(Application PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glm.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/graphics/graphics.hpp"
)

target_link_libraries(Application PUBLIC vendor)

target_sources(Application PRIVATE
    "${CMAKE_SOURCE_DIR}/VegaEngine/vendor/imgui/imgui.cpp"

    "${CMAKE_SOURCE_DIR}/VegaEngine/vendor/imgui/imgui_demo.cpp"
    "${CMAKE_SOURCE_DIR}/VegaEngine/vendor/imgui/imgui_draw.cpp"
    "${CMAKE_SOURCE_DIR}/VegaEngine/vendor/imgui/imgui_tables.cpp"
    "${CMAKE_SOURCE_DIR}/VegaEngine/vendor/imgui/imgui_widgets.cpp"

    "${CMAKE_SOURCE_DIR}/VegaEngine/vendor/imgui/backends/imgui_impl_vulkan.cpp"
    "${CMAKE_SOURCE_DIR}/VegaEngine/vendor/imgui/backends/imgui_impl_sdl3.cpp"

    "${CMAKE_SOURCE_DIR}/VegaEngine/vendor/imgui/misc/cpp/imgui_stdlib.cpp"
)

target_include_directories(Application PUBLIC
    "${CMAKE_SOURCE_DIR}/VegaEngine/vendor/imgui"
    "${CMAKE_SOURCE_DIR}/VegaEngine/vendor/imgui/backends"
)
