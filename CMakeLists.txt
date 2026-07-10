cmake_minimum_required(VERSION 4.2.3)

project(VegaEngine
    VERSION 0.0.1
    DESCRIPTION "A graphics and scientific computing library"
    HOMEPAGE_URL "https://github.com/Poivre31/vega-engine"
    LANGUAGES CXX
)



if(CMAKE_SYSTEM MATCHES Windows)
   message(TRACE "Building for Windows")
elseif(CMAKE_SYSTEM MATCHES Linux)
   message(TRACE "Building for Linux")
endif()

add_executable(VegaEngine)

add_subdirectory(libs/math)
target_link_libraries(VegaEngine PRIVATE Math)
target_include_directories(VegaEngine PRIVATE libs/math/include)

target_sources(VegaEngine PRIVATE src/main.cpp)
