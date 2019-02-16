#include "debug.hpp"

namespace {
std::string sourceToString(GLenum source) {
    switch (source) {
        case GL_DEBUG_SOURCE_API:
            return "Source: API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return "Source: Window System";
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return "Source: Shader Compiler";
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            return "Source: Third Party";
        case GL_DEBUG_SOURCE_APPLICATION:
            return "Source: Application";
        case GL_DEBUG_SOURCE_OTHER:
        default:
            return "Source: Other";
    }
}

std::string typeToString(GLenum type) {
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            return "Type: Error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return "Type: Deprecated Behaviour";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return "Type: Undefined Behaviour";
        case GL_DEBUG_TYPE_PORTABILITY:
            return "Type: Portability";
        case GL_DEBUG_TYPE_PERFORMANCE:
            return "Type: Performance";
        case GL_DEBUG_TYPE_MARKER:
            return "Type: Marker";
        case GL_DEBUG_TYPE_PUSH_GROUP:
            return "Type: Push Group";
        case GL_DEBUG_TYPE_POP_GROUP:
            return "Type: Pop Group";
        case GL_DEBUG_TYPE_OTHER:
        default:
            return "Type: Other";
    }
}

std::string severityToString(GLenum severity) {
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            return "Severity: high";
        case GL_DEBUG_SEVERITY_MEDIUM:
            return "Severity: medium";
        case GL_DEBUG_SEVERITY_LOW:
            return "Severity: low";
        case GL_DEBUG_SEVERITY_NOTIFICATION:
        default:
            return "Severity: notification";
    }
}

} // namespace

using DebugCallbackFunction = void (*)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *, void *);
using GLDebugMessageCallback = ExtensionFunction<void(DebugCallbackFunction callback, const void *userParam)>;

Debug::Debug(const Extensions &extensions) {
    GLDebugMessageCallback debugMessageCallback{
            extensions.load({{"GL_KHR_debug",        "glDebugMessageCallback"},
                             {"GL_ARB_debug_output", "glDebugMessageCallbackARB"}})
    };

    if (debugMessageCallback) {
        debugMessageCallback.operator()(
                [](GLenum source, GLenum type, GLuint id, GLenum severity,
                   GLsizei length, const GLchar *message, void *userParam) {

                    // ignore non-significant error/warning codes
                    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

                    std::cout << "---------------" << std::endl;
                    std::cout << "Debug message (" << id << "): "
                              << message
                              << " " << sourceToString(source)
                              << " " << typeToString(type)
                              << " " << severityToString(severity) << std::endl;
                }, nullptr);
    }
}
