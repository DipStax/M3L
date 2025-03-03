cmake_minimum_required(VERSION 3.24)

project(M3L_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

include (cmake/Interface.cmake)
include (cmake/Network.cmake)
include (cmake/Graphics.cmake)
include (cmake/Event.cmake)

add_subdirectory(demo)