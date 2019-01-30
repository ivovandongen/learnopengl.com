git_include(glfw)
include(${CMAKE_SOURCE_DIR}/deps/glad.cmake)

# Get executable name
get_filename_component(EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_executable(${EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

target_link_libraries(${EXECUTABLE} PUBLIC
        glfw
        glad
        )

if (DO_CLANG_TIDY)
    set_target_properties(${EXECUTABLE} PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()