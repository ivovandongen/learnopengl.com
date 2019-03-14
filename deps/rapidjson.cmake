
include_guard_x()

add_library(rapidjson INTERFACE)
target_include_directories(rapidjson SYSTEM INTERFACE ${CMAKE_SOURCE_DIR}/deps/rapidjson/include)