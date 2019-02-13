#include "texture.hpp"

#include <stb_image.h>

namespace {

GLenum toGLFormat(int channels, bool gammaCorrected = false) {
    switch (channels) {
        case 1:
            return GL_RED;
        case 3:
            return gammaCorrected ? GL_SRGB : GL_RGB;
        case 4:
            return gammaCorrected ? GL_SRGB_ALPHA : GL_RGBA;
        default:
            return gammaCorrected ? GL_SRGB : GL_RGB;;
    }
}

} // namespace

Texture::Texture(const Image &image, bool generateMipmap, bool gammaCorrected)
        : _target(GL_TEXTURE_2D) {

    glGenTextures(1, &_id);
    glBindTexture(_target, _id);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    if (image.channels() == 4) {
        // Note that when sampling textures at their borders, OpenGL interpolates
        // the border values with the next repeated value of the texture (because
        // we set its wrapping parameters to GL_REPEAT). This is usually okay, but
        // since we're using transparent values, the top of the texture image gets
        // its transparent value interpolated with the bottom border's solid color
        // value. The result is then a slightly semi-transparent colored border
        // you might see wrapped around your textured quad. To prevent this, set
        // the texture wrapping method to GL_CLAMP_TO_EDGE whenever you use alpha
        // textures
        glTexParameteri(_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    } else {
        glTexParameteri(_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = toGLFormat(image.channels());
    GLenum internalFormat = toGLFormat(image.channels(), gammaCorrected);

    glTexImage2D(_target, 0, internalFormat, image.width(), image.height(), 0, format, GL_UNSIGNED_BYTE, image.data());

    if (generateMipmap) {
        glGenerateMipmap(_target);
    }
}

Texture::Texture(const std::array<const Image, 6> &images, bool generateMipmap, bool gammaCorrected)
        : _target(GL_TEXTURE_CUBE_MAP) {
    glGenTextures(1, &_id);
    glBindTexture(_target, _id);

    for (unsigned int i = 0; i < images.size(); i++) {
        const auto &image = images[i];
        GLenum format = toGLFormat(image.channels());
        GLenum internalFormat = toGLFormat(image.channels(), gammaCorrected);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, image.width(), image.height(), 0, format,
                     GL_UNSIGNED_BYTE, image.data());
    }

    glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(_target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    if (generateMipmap) {
        glGenerateMipmap(_target);
    }
}

Texture::Texture(unsigned int width, unsigned int height, unsigned int samples)
        : _target(samples > 1 ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D) {
    glGenTextures(1, &_id);
    glBindTexture(_target, _id);

    if (samples > 1) {
        glTexImage2DMultisample(_target, samples, GL_RGB, width, height, GL_TRUE);
    } else {
        glTexImage2D(_target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

}

Texture::~Texture() {
    glDeleteTextures(1, &_id);
}

void Texture::bind() const {
    glBindTexture(_target, _id);
}

void Texture::unbind() const {
    glBindTexture(_target, 0);
}
