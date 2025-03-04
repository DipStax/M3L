include_guard()

# SYSTEM
if (NOT TARGET M3L_TOOL)
    include (cmake/Tool.cmake)
endif ()

file (GLOB_RECURSE SRC_M3L_SYSTEM
    include/M3L/System/**.inl
    include/M3L/System/**.hpp
    src/System/**.cpp
)
msvc_source_file (SRC_M3L_SYSTEM)

add_library (M3L_SYSTEM
    SHARED
        ${SRC_M3L_SYSTEM}
)

target_link_libraries (M3L_SYSTEM
    PUBLIC
        M3L_INTERFACE
        M3L_TOOL
)
