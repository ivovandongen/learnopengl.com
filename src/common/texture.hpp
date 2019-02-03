#pragma once

#include <glad/glad.h>
#include <image.hpp>

class Texture {
public:
    explicit Texture(const Image &image, bool generateMipmap = true);

    ~Texture();

    void bind() const;

    void unbind() const;

private:
    GLuint _id{0};
};