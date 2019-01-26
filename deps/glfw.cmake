include_guard_x()

set(GLFW_DIR ${CMAKE_SOURCE_DIR}/deps/glfw)

set(GLFW_VERSION_MAJOR "3")
set(GLFW_VERSION_MINOR "3")
set(GLFW_VERSION_PATCH "0")
set(GLFW_VERSION_EXTRA "")
set(GLFW_VERSION "${GLFW_VERSION_MAJOR}.${GLFW_VERSION_MINOR}")
set(GLFW_VERSION_FULL "${GLFW_VERSION}.${GLFW_VERSION_PATCH}${GLFW_VERSION_EXTRA}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#if (GLFW_USE_WAYLAND)
#    set(_GLFW_WAYLAND 1)
#    message(FATAL "Using Wayland for window creation")
#elseif (GLFW_USE_OSMESA)
#    set(_GLFW_OSMESA 1)
#    message(STATUS "Using OSMesa for headless context creation")
#elseif (WIN32)
#    set(_GLFW_WIN32 1)
#    message(STATUS "Using Win32 for window creation")
#else
if (APPLE)
    set(_GLFW_COCOA 1)
    message(STATUS "Using Cocoa for window creation")
    #elseif (UNIX)
    #    set(_GLFW_X11 1)
    #    message(STATUS "Using X11 for window creation")

    # For some reason, CMake doesn't know about .m
    set_source_files_properties(${glfw_SOURCES} PROPERTIES LANGUAGE C)
else ()
    message(FATAL_ERROR "No supported platform was detected")
endif ()

if (_GLFW_COCOA)
    set(GLFW_PLATFORM_SOURCES
            ${GLFW_DIR}/src/cocoa_init.m
            ${GLFW_DIR}/src/cocoa_joystick.m
            ${GLFW_DIR}/src/cocoa_monitor.m
            ${GLFW_DIR}/src/cocoa_window.m
            ${GLFW_DIR}/src/cocoa_time.c
            ${GLFW_DIR}/src/posix_tls.c
            ${GLFW_DIR}/src/nsgl_context.m
            )

    # For some reason, CMake doesn't know about .m
    set_source_files_properties(${GLFW_PLATFORM_SOURCES} PROPERTIES LANGUAGE C)

    list(APPEND GLFW_LIBRARIES
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreFoundation"
            "-framework CoreVideo")

#    set(glfw_PKG_DEPS "")
#    set(glfw_PKG_LIBS "-framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreVideo")
endif ()

add_library(glfw STATIC
        ${GLFW_DIR}/src/glfw_config.h
        ${GLFW_DIR}/src/context.c
        ${GLFW_DIR}/src/init.c
        ${GLFW_DIR}/src/input.c
        ${GLFW_DIR}/src/monitor.c
        ${GLFW_DIR}/src/vulkan.c
        ${GLFW_DIR}/src/window.c
        ${GLFW_PLATFORM_SOURCES}
        )

if (_GLFW_COCOA)
    target_compile_definitions(glfw PRIVATE _GLFW_COCOA)
endif()

target_include_directories(glfw
        PRIVATE ${GLFW_DIR}/src
        PRIVATE ${GLFW_DIR}/include
        )

target_include_directories(glfw
        SYSTEM INTERFACE ${GLFW_DIR}/include
        )

target_link_libraries(glfw INTERFACE ${GLFW_LIBRARIES})