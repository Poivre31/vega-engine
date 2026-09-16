cmake_minimum_required(VERSION 3.28)

# ------------------
# ------------------
project(VulkanApp
   VERSION 0.0.1
   DESCRIPTION "A basic 3D renderer"
   LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "-O1 -g")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g")

# ------------------
# ------------------
add_executable(VulkanApp src/main.cpp)
target_link_libraries(VulkanApp VegaEngine)

add_custom_target(CopyShaders
    COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_CURRENT_BINARY_DIR}/resources"
    COMMENT "Copying resources: ${CMAKE_CURRENT_SOURCE_DIR}/resources to ${CMAKE_CURRENT_BINARY_DIR}/resources"
)
add_dependencies(VulkanApp CopyShaders)

if(WIN32)
    add_custom_command(TARGET VulkanApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:VulkanApp>
            "${CMAKE_CURRENT_BINARY_DIR}"
        COMMAND_EXPAND_LISTS
    )
elseif(UNIX)
    set_target_properties(VulkanApp PROPERTIES
        BUILD_RPATH "${CMAKE_CURRENT_BINARY_DIR}"
        INSTALL_RPATH "$ORIGIN"
        BUILD_RPATH_USE_ORIGIN TRUE
    )
endif()


install(DIRECTORY resources DESTINATION .)
install(TARGETS VulkanApp DESTINATION .)

# target_compile_options(VulkanApp PRIVATE -O0 -g -fsanitize=address -fno-omit-frame-pointer)
# target_link_options(VulkanApp PRIVATE -O0 -g -fsanitize=address -fno-omit-frame-pointer)
