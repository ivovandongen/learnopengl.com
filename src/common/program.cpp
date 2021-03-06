#include "program.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace {

inline std::string shaderType(GLenum type) {
    switch (type) {
        case GL_VERTEX_SHADER :
            return "Vertex";
        case GL_GEOMETRY_SHADER :
            return "Geometry";
        case GL_FRAGMENT_SHADER :
            return "Fragment";
        default:
            return "UNKNOWN";
    }
}

GLuint loadShader(GLuint program, const std::string &shaderSource, GLuint type) {
    GLuint shaderId = glCreateShader(type);
    auto source = shaderSource.c_str();
    const GLint length = shaderSource.length();
    glShaderSource(shaderId, 1, &source, &length);
    glCompileShader(shaderId);
    GLint compileStatus;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
        std::string message = std::string("Could not compile ")
                              + shaderType(type) + " shader\n" +
                              errorLog.data();
        std::cout << message << std::endl;
    }
    glAttachShader(program, shaderId);

    return shaderId;
}

} // namespace

Program::Program(const std::string &vert, const std::string &frag) {
    _id = glCreateProgram();
    auto vertexShader = loadShader(_id, vert, GL_VERTEX_SHADER);
    auto fragmentShader = loadShader(_id, frag, GL_FRAGMENT_SHADER);

    glLinkProgram(_id);
    glValidateProgram(_id);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Program::Program(const std::string &vert, const std::string &geom, const std::string &frag) {
    _id = glCreateProgram();
    auto vertexShader = loadShader(_id, vert, GL_VERTEX_SHADER);
    auto geometryShader = loadShader(_id, geom, GL_GEOMETRY_SHADER);
    auto fragmentShader = loadShader(_id, frag, GL_FRAGMENT_SHADER);

    glLinkProgram(_id);
    glValidateProgram(_id);
    glDeleteShader(vertexShader);
    glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);
}

Program::~Program() {
    glDeleteProgram(_id);
}

void Program::bind() {
    glUseProgram(_id);
}

void Program::unbind() {
    glUseProgram(0);
}

GLuint Program::id() {
    return _id;
}

