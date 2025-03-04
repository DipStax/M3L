include_guard()

# NETWORK

if (NOT TARGET M3L_SYSTEM)
    include (cmake/System.cmake)
endif ()

file (GLOB_RECURSE SRC_M3L_NETWORK
    include/M3L/Network/**.inl
    include/M3L/Network/**.hpp
    src/Network/**.cpp
)
msvc_source_file (SRC_M3L_NETWORK)

add_library (M3L_NETWORK
    SHARED
        ${SRC_M3L_NETWORK}
)

target_link_libraries (M3L_NETWORK
    PUBLIC
        M3L_INTERFACE
        M3L_SYSTEM
    PRIVATE
        wsock32
        ws2_32
)

