#pragma once

#include <id.hpp>
#include <image.hpp>

#include <glad/glad.h>
#include <array>
#include <iostream>

class Texture {
public:
    static Texture createDepthAttachmentTexture(unsigned int width, unsigned int height);

    /**
     * Create 2D texture from image
     */
    explicit Texture(const Image &image, bool generateMipmap = true, bool gammaCorrected = false);

    /**
     * Create a cubemap from a set of images
     */
    explicit Texture(const std::array<const Image, 6> &images, bool generateMipmap = true, bool gammaCorrected = false);

    /**
     * Create a sized texture for use in a framebuffer
     */
    Texture(unsigned int width, unsigned int height, unsigned int samples = 1);

    ~Texture();

    Texture(Texture &&) = default;

    Texture &operator=(Texture &&) = default;

    GLuint id() const {
        return *_id;
    }

    void bind() const;

    void unbind() const;

protected:
    /**
     * Create texture to be configured
     */
    explicit Texture(GLenum target);

private:
    ID<GLuint> _id;
    GLenum _target;
};