include_guard_x()

set(GLFW_DIR ${CMAKE_SOURCE_DIR}/deps/glfw)

set(GLFW_VERSION_MAJOR "3")
set(GLFW_VERSION_MINOR "3")
set(GLFW_VERSION_PATCH "0")
set(GLFW_VERSION_EXTRA "")
set(GLFW_VERSION "${GLFW_VERSION_MAJOR}.${GLFW_VERSION_MINOR}")
set(GLFW_VERSION_FULL "${GLFW_VERSION}.${GLFW_VERSION_PATCH}${GLFW_VERSION_EXTRA}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Threads REQUIRED)

if (APPLE)
    set(_GLFW_COCOA 1)
    message(STATUS "Using Cocoa for window creation")
elseif (UNIX)
    set(_GLFW_X11 1)
    message(STATUS "Using X11 for window creation")
else ()
    message(FATAL_ERROR "No supported platform was detected")
endif ()

#--------------------------------------------------------------------
# Find and add Unix math and time libraries
#--------------------------------------------------------------------
if (UNIX AND NOT APPLE)
    find_library(RT_LIBRARY rt)
    if (RT_LIBRARY)
        list(APPEND GLFW_LIBRARIES "${RT_LIBRARY}")
    endif ()

    find_library(MATH_LIBRARY m)
    mark_as_advanced(MATH_LIBRARY)
    if (MATH_LIBRARY)
        list(APPEND GLFW_LIBRARIES "${MATH_LIBRARY}")
    endif ()

    if (CMAKE_DL_LIBS)
        list(APPEND GLFW_LIBRARIES "${CMAKE_DL_LIBS}")
    endif ()
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
endif ()

if (_GLFW_X11)
    find_package(X11 REQUIRED)

    # Set up library and include paths
    list(APPEND GLFW_INCLUDE_DIRS "${X11_X11_INCLUDE_PATH}")
    list(APPEND GLFW_LIBRARIES "${X11_X11_LIB}" "${CMAKE_THREAD_LIBS_INIT}")

    # Check for XRandR (modern resolution switching and gamma control)
    if (NOT X11_Xrandr_FOUND)
        message(FATAL_ERROR "The RandR library and headers were not found")
    endif ()

    list(APPEND GLFW_INCLUDE_DIRS "${X11_Xrandr_INCLUDE_PATH}")
    list(APPEND GLFW_LIBRARIES "${X11_Xrandr_LIB}")

    # Check for Xinerama (legacy multi-monitor support)
    if (NOT X11_Xinerama_FOUND)
        message(FATAL_ERROR "The Xinerama library and headers were not found")
    endif ()

    list(APPEND GLFW_INCLUDE_DIRS "${X11_Xinerama_INCLUDE_PATH}")
    list(APPEND GLFW_LIBRARIES "${X11_Xinerama_LIB}")

    # Check for Xf86VidMode (fallback gamma control)
    if (X11_xf86vmode_FOUND)
        list(APPEND GLFW_INCLUDE_DIRS "${X11_xf86vmode_INCLUDE_PATH}")
        list(APPEND glfw_PKG_DEPS "xxf86vm")

        if (X11_Xxf86vm_LIB)
            list(APPEND GLFW_LIBRARIES "${X11_Xxf86vm_LIB}")
        else ()
            # Backwards compatibility (see CMake bug 0006976)
            list(APPEND GLFW_LIBRARIES Xxf86vm)
        endif ()

        set(_GLFW_HAS_XF86VM TRUE)
    endif ()

    # Check for Xkb (X keyboard extension)
    if (NOT X11_Xkb_FOUND)
        message(FATAL_ERROR "The X keyboard extension headers were not found")
    endif ()

    list(APPEND GLFW_INCLUDE_DIR "${X11_Xkb_INCLUDE_PATH}")

    # Check for Xcursor
    if (NOT X11_Xcursor_FOUND)
        message(FATAL_ERROR "The Xcursor libraries and headers were not found")
    endif ()

    list(APPEND GLFW_INCLUDE_DIR "${X11_Xcursor_INCLUDE_PATH}")
    list(APPEND GLFW_LIBRARIES "${X11_Xcursor_LIB}")

    set(GLFW_PLATFORM_SOURCES
            ${GLFW_DIR}/src/x11_init.c
            ${GLFW_DIR}/src/x11_monitor.c
            ${GLFW_DIR}/src/x11_window.c
            ${GLFW_DIR}/src/xkb_unicode.c
            ${GLFW_DIR}/src/linux_joystick.c
            ${GLFW_DIR}/src/posix_time.c
            ${GLFW_DIR}/src/posix_tls.c
            ${GLFW_DIR}/src/glx_context.c
            ${GLFW_DIR}/src/egl_context.c
            )
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
elseif (_GLFW_X11)
    target_compile_definitions(glfw PRIVATE _GLFW_X11)
endif ()

target_include_directories(glfw
        PRIVATE ${GLFW_DIR}/src
        PRIVATE ${GLFW_DIR}/include
        PRIVATE ${GLFW_INCLUDE_DIRS}
        )

target_include_directories(glfw
        SYSTEM INTERFACE ${GLFW_DIR}/include
        SYSTEM INTERFACE ${GLFW_INCLUDE_DIR}
        )

target_link_libraries(glfw INTERFACE ${GLFW_LIBRARIES})