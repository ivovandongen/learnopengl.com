
include_guard_x()

add_library(glm INTERFACE)
target_include_directories(glm SYSTEM INTERFACE ${CMAKE_SOURCE_DIR}/deps/glm)
