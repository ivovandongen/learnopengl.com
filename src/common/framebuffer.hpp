#pragma once

#include <texture.hpp>

#include <glad/glad.h>
#include <tl/optional.hpp>

class Framebuffer {
public:
    static void bindDefault();

    Framebuffer(unsigned int width, unsigned int height);

    ~Framebuffer();

    void bind() const;

    void unbind() const;

    bool bound() const;

    bool ready() const;

    const Texture& texture();

private:
    GLuint _id;
    tl::optional<Texture> _texture;
    GLuint rbo = 0;
};