include_guard()

add_library(M3L_INTERFACE INTERFACE)

target_compile_options(M3L_INTERFACE INTERFACE /W4)
target_compile_definitions(M3L_INTERFACE INTERFACE NOMINMAX _USE_MATH_DEFINES MMML_EXPORTS)
target_include_directories(M3L_INTERFACE INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

function(msvc_source_file src_file)
    foreach(file IN LISTS ${src_file})
        get_filename_component(file_path "${file}" PATH)
        file(RELATIVE_PATH rfile_path "${CMAKE_SOURCE_DIR}" "${file_path}")
        string(REPLACE "/" "\\" file_path_msvc "${rfile_path}")
        source_group("${file_path_msvc}" FILES "${file}")
    endforeach()
endfunction()
