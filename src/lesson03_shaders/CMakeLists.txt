git_include(glfw)
include(${CMAKE_SOURCE_DIR}/deps/glad.cmake)

add_executable(lesson03
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

target_link_libraries(lesson03 PUBLIC
        glfw
        glad
        common
        )

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.glsl")
foreach(file ${files})
    configure_file(${file} ${CMAKE_CURRENT_BINARY_DIR}  COPYONLY)
endforeach()

if (DO_CLANG_TIDY)
    set_target_properties(lesson03 PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()