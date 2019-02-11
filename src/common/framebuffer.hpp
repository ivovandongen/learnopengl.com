#pragma once

#include <texture.hpp>

#include <glad/glad.h>
#include <tl/optional.hpp>

class Framebuffer {
public:
    enum class BindMode {
        READ,
        DRAW,
        READ_WRITE
    };

    static void bindDefault(BindMode mode = BindMode::READ_WRITE);

    Framebuffer(unsigned int width, unsigned int height, unsigned int samples = 1);

    ~Framebuffer();

    void bind(BindMode mode = BindMode::READ_WRITE) const;

    void unbind() const;

    bool bound() const;

    bool ready() const;

    GLuint id() const {
        return _id;
    }

    const Texture &texture();

private:
    GLuint _id;
    tl::optional<Texture> _texture;
    GLuint rbo = 0;
};