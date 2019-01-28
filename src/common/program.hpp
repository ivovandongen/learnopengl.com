#pragma once

#include <glad/glad.h>

#include <string>

class Program {

public:
    Program(const std::string &vert, const std::string &frag);

    ~Program();

    GLuint id();

    void bind();

    void unbind();

private:
    GLuint _id;
};