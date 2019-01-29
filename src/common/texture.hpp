#pragma once

#include <glad/glad.h>
#include <image.hpp>

class Texture {
public:
    Texture(const Image &image, bool generateMipmap = true);

    ~Texture();

    void bind();

    void unbind();

private:
    GLuint _id;
};