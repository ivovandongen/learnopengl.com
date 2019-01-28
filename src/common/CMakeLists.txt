git_include(glfw)
include(${CMAKE_SOURCE_DIR}/deps/glad.cmake)

add_library(common STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/file.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/program.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/program.hpp
        )

target_link_libraries(common PUBLIC
        glad
        )

target_include_directories(common PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

if (DO_CLANG_TIDY)
    set_target_properties(common PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()