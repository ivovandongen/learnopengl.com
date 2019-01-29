
include_guard_x()

add_library(stb INTERFACE)
target_include_directories(stb SYSTEM INTERFACE ${CMAKE_SOURCE_DIR}/deps/stb)
