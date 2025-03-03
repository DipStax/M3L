include_guard()

# GRAPHICS

if (NOT TARGET M3L_SYSTEM)
    include (cmake/System.cmake)
endif ()
if (NOT TARGET M3L_EVENT)
    include (cmake/Event.cmake)
endif ()

file (GLOB_RECURSE SRC_M3L_GRAPHICS
    include/M3L/Graphics/**.inl
    include/M3L/Graphics/**.hpp
    src/Graphics/**.cpp
)
msvc_source_file (SRC_M3L_GRAPHICS)

add_library (M3L_GRAPHICS
    SHARED
        ${SRC_M3L_GRAPHICS}
)

target_link_libraries (M3L_GRAPHICS
    PUBLIC
        M3L_INTERFACE
        M3L_SYSTEM
        M3L_EVENT
)

