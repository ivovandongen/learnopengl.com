include_guard_x()

set(GLAD_DIR ${CMAKE_SOURCE_DIR}/deps/glad)


add_library(glad STATIC
        ${GLAD_DIR}/include/glad/glad.h
        ${GLAD_DIR}/src/glad.c
        )

target_include_directories(glad
        PRIVATE ${GLAD_DIR}/include
        )

target_include_directories(glad
        SYSTEM INTERFACE ${GLAD_DIR}/include
        )