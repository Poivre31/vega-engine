add_library(Math
    "src/integration/trapezium.cpp"
)

target_include_directories(Math PUBLIC
    "include"
)


target_link_libraries(Math PUBLIC Console)

add_subdirectory(bench)

if(MSVC)
    target_compile_options(Math PRIVATE -Wall -W4)
else()
    target_compile_options(Math PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()
