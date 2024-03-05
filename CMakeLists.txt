cmake_minimum_required(VERSION 3.24)

project(M3L_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

file(GLOB_RECURSE SRC_M3L
    include/**.inl
    src/**.cpp
)

add_library(M3L SHARED
    ${SRC_M3L}
)

target_include_directories(M3L PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(M3L PUBLIC MMML_EXPORTS)

if (MSVC)
    target_compile_options(M3L PRIVATE /W4)
    target_compile_definitions(M3L PUBLIC NOMINMAX)
else ()
    target_compile_options(M3L PRIVATE -Wall -Wextra -g3)
endif ()

add_subdirectory(demo)