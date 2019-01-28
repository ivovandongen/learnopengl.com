add_subdirectory(common)

file(GLOB lessons "${CMAKE_CURRENT_SOURCE_DIR}/lesson*")
foreach(lesson ${lessons})
    add_subdirectory(${lesson})
endforeach()
