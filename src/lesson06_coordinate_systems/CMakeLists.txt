git_include(glfw)
git_include(glm)
include(${CMAKE_SOURCE_DIR}/deps/glad.cmake)

add_executable(lesson06
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

target_link_libraries(lesson06 PUBLIC
        glfw
        glad
        glm
        common
        )

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.glsl" "${CMAKE_CURRENT_SOURCE_DIR}/*.jpg" "${CMAKE_CURRENT_SOURCE_DIR}/*.png")
foreach(file ${files})
    configure_file(${file} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()

if (DO_CLANG_TIDY)
    set_target_properties(lesson06 PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()