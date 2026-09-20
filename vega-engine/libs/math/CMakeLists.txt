add_library(math STATIC
    "src/integration/trapezium.cpp"
)

target_include_directories(math PUBLIC
    "include"
)


target_link_libraries(math PUBLIC console)

add_subdirectory(bench)

if(MSVC)
    target_compile_options(math PRIVATE -Wall -W4)
else()
    target_compile_options(math PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()
