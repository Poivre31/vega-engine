cmake_minimum_required(VERSION 3.28)

# ------------------
# ------------------
project(vega-engine
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


add_subdirectory(vendor)

# ------------------
add_library(vega-engine STATIC)

add_subdirectory(libs/math)
target_link_libraries(vega-engine PUBLIC math)
add_subdirectory(libs/math/tests)

add_subdirectory(libs/console)
target_link_libraries(vega-engine PUBLIC console)
add_subdirectory(libs/console/tests)

add_subdirectory(libs/timer)
target_link_libraries(vega-engine PUBLIC timer)
add_subdirectory(libs/timer/tests)

add_subdirectory(libs/application)
target_link_libraries(vega-engine PUBLIC Application)

target_sources(vega-engine PRIVATE src/implementations.cpp)

# ------------------
# ------------------
if(MSVC)
   target_compile_options(vega-engine PRIVATE -Wall -W4)
else()
   target_compile_options(vega-engine PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()
target_compile_options(vega-engine PRIVATE -march=x86-64 -mtune=generic)
