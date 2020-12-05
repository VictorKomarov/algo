cmake_minimum_required(VERSION 3.5)

project(sort)

add_executable(gen
    src/generator.cpp
)

set_target_properties(gen PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_compile_options(gen PRIVATE
    -Wall -Wextra -pedantic -Werror
)

add_executable(sort
    src/external_sort.cpp
    src/sort.cpp
)

set_target_properties(sort PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(sort
    PRIVATE
        include/
)

target_compile_options(sort PRIVATE
    -Wall -Wextra -pedantic -Werror
)