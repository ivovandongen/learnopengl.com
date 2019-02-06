#pragma once

#include <glad/glad.h>
#include <image.hpp>

class Texture {
public:
    explicit Texture(const Image &image, bool generateMipmap = true);

    Texture(unsigned int width, unsigned int height);

    ~Texture();

    GLuint id() const {
        return _id;
    }

    void bind() const;

    void unbind() const;

private:
    GLuint _id{0};
};