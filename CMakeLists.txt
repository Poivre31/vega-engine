cmake_minimum_required(VERSION 3.28.3)

# ------------------
# ------------------
project(VegaEngine
   VERSION 0.0.1
   DESCRIPTION "A graphics and scientific computing library"
   HOMEPAGE_URL "https://github.com/Poivre31/vega-engine"
   LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM MATCHES Windows)
   message(TRACE "Building for Windows")
elseif(CMAKE_SYSTEM MATCHES Linux)
   message(TRACE "Building for Linux")
endif()


# ------------------
# ------------------
include(CTest)
enable_testing()

add_subdirectory(external)

# ------------------
add_executable(VegaEngine)

add_subdirectory(libs/math)
target_link_libraries(VegaEngine PRIVATE Math)
add_subdirectory(libs/math/tests)

# ------------------
# add_subdirectory(libs/console)
# target_link_libraries(VegaEngine PRIVATE Console)

target_sources(VegaEngine PRIVATE src/main.cpp)


# ------------------
# ------------------
target_compile_options(VegaEngine PRIVATE -Wall -Wextra)
