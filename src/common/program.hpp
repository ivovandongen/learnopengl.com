#pragma once

#include <glad/glad.h>

#include <string>

class Program {

public:
    Program(const std::string &vert, const std::string &frag);

    ~Program();

    void bind();

    void unbind();

private:
    GLuint id;
};