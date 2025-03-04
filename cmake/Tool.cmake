include_guard()

# TOOL

file (GLOB_RECURSE SRC_M3L_TOOL
    include/Tool/**.inl
    include/Tool/**.hpp
    src/Tool/**.cpp
)
msvc_source_file (SRC_M3L_TOOL)

add_library (M3L_TOOL
    STATIC
        ${SRC_M3L_TOOL}
)
target_link_libraries (M3L_TOOL
    PUBLIC
        M3L_INTERFACE
)

target_include_directories(M3L_TOOL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/Tool)