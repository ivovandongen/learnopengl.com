git_include(assimp)
git_include(glfw)
git_include(glm)
git_include(stb)
include(${CMAKE_SOURCE_DIR}/deps/glad.cmake)

add_library(common STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/camera.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/file.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/image.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/image.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mesh.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mesh.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/model.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/model.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/program.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/program.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture.hpp
        )

target_link_libraries(common PUBLIC
        assimp
        glad
        stb
        glm
        )

target_include_directories(common PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

if (DO_CLANG_TIDY)
    set_target_properties(common PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif ()