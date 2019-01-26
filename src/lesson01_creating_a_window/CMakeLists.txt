git_include(glfw)
include(${CMAKE_SOURCE_DIR}/deps/glad.cmake)

add_executable(lesson01
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

target_link_libraries(lesson01 PUBLIC
        glfw
        glad
        )

if (DO_CLANG_TIDY)
    set_target_properties(lesson01 PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()