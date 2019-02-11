#pragma once

#include <image.hpp>

#include <glad/glad.h>
#include <array>

class Texture {
public:
    /**
     * Create 2D texture from image
     */
    explicit Texture(const Image &image, bool generateMipmap = true);

    /**
     * Create a cubemap from a set of images
     */
    explicit Texture(const std::array<const Image, 6> &images, bool generateMipmap = true);

    /**
     * Create a sized texture for use in a framebuffer
     */
    Texture(unsigned int width, unsigned int height, unsigned int samples = 1);

    ~Texture();

    GLuint id() const {
        return _id;
    }

    void bind() const;

    void unbind() const;

private:
    GLuint _id{0};
    GLenum _target;
};