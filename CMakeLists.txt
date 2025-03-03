cmake_minimum_required(VERSION 3.24)

project(M3L_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SRC_M3L
    include/**.inl
    include/**.hpp
    src/**.cpp
)

add_library(M3L SHARED
    ${SRC_M3L}
)

target_include_directories(M3L PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(M3L PUBLIC MMML_EXPORTS)

if (MSVC)
    target_compile_options(M3L PRIVATE /W4)
    target_compile_definitions(M3L PUBLIC NOMINMAX _USE_MATH_DEFINES)
    target_link_libraries(M3L wsock32 ws2_32)

    foreach(file IN LISTS SRC_M3L)
        get_filename_component(file_path "${file}" PATH)
        file(RELATIVE_PATH rfile_path "${CMAKE_SOURCE_DIR}" "${file_path}")
        string(REPLACE "/" "\\" file_path_msvc "${rfile_path}")
        source_group("${file_path_msvc}" FILES "${file}")
    endforeach()

else ()
    target_compile_options(M3L PRIVATE -Wall -Wextra -g3)
endif ()

add_subdirectory(demo)