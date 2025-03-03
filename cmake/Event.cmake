include_guard()

# EVENT

if (NOT TARGET M3L_SYSTEM)
    include (cmake/System.cmake)
endif ()

file (GLOB_RECURSE SRC_M3L_EVENT
    include/M3L/Event/**.inl
    include/M3L/Event/**.hpp
    src/Event/**.cpp
)
msvc_source_file (SRC_M3L_EVENT)

add_library (M3L_EVENT
    SHARED
        ${SRC_M3L_EVENT}
)

target_link_libraries (M3L_EVENT
    PUBLIC
        M3L_INTERFACE
        M3L_SYSTEM
)

