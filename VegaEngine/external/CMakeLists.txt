set(CMAKE_CXX_STANDARD 20)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(google_test)

add_subdirectory(nanobench)

add_subdirectory(spdlog)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
add_subdirectory(sdl)

find_package(Vulkan REQUIRED)

add_library(ImGui)
target_link_libraries(ImGui PUBLIC
    SDL3::SDL3-static
    Vulkan::Vulkan
)

target_include_directories(ImGui PUBLIC imgui/)
target_include_directories(ImGui PUBLIC imgui/backends/)

target_sources(ImGui PRIVATE
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp
)

target_sources(ImGui PRIVATE
    imgui/backends/imgui_impl_sdl3.cpp
    imgui/backends/imgui_impl_vulkan.cpp
)

target_sources(ImGui PRIVATE
    imgui/misc/cpp/imgui_stdlib.cpp
)

