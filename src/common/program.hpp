#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Program {

public:
    Program(const std::string &vert, const std::string &frag);

    ~Program();

    GLuint id();

    void bind();

    void unbind();

    void inline setUniform(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(_id, name.c_str()), (int) value);
    }

    void inline setUniform(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
    }

    void inline setUniform(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
    }

    void inline setUniform(const std::string &name, float x, float y) const {
        glUniform2f(glGetUniformLocation(_id, name.c_str()), x, y);
    }

    void inline setUniform(const std::string &name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(_id, name.c_str()), x, y, z);
    }

    void inline setUniform(const std::string &name, float x, float y, float z, float w) const {
        glUniform4f(glGetUniformLocation(_id, name.c_str()), x, y, z, w);
    }

    void inline setUniform(const std::string &name, glm::vec3 value) const {
        glUniform3f(glGetUniformLocation(_id, name.c_str()), value.x, value.y, value.z);
    }

    void inline setUniform(const std::string &name, glm::mat4 value) const {
        glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

private:
    GLuint _id;
};