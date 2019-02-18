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

    glGenTextures(1, &*_id);
    glBindTexture(_target, *_id);

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
    glGenTextures(1, &*_id);
    glBindTexture(_target, *_id);

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

Texture::Texture(unsigned int width, unsigned int height, unsigned int samples, bool floatingPoint)
        : _target(samples > 1 ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D) {
    glGenTextures(1, &*_id);
    glBindTexture(_target, *_id);

    if (samples > 1) {
        glTexImage2DMultisample(_target, samples, floatingPoint ? GL_RGB16F : GL_RGB, width, height, GL_TRUE);
    } else {
        glTexImage2D(_target, 0, floatingPoint ? GL_RGB16F : GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

Texture::~Texture() {
    if (_id) {
        glDeleteTextures(1, &*_id);
    }
}

void Texture::bind() const {
    glBindTexture(_target, *_id);
}

void Texture::unbind() const {
    glBindTexture(_target, 0);
}

Texture::Texture(GLenum target) : _target(target) {
    glGenTextures(1, &*_id);
    glBindTexture(_target, *_id);
}

Texture Texture::createDepthAttachmentTexture(unsigned int width, unsigned int height, bool cubeMap) {
    GLenum type = cubeMap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;
    Texture texture{type};

    if (cubeMap) {
        for (unsigned int i = 0; i < 6; ++i) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, width, height, 0,
                         GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    }
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(type, GL_TEXTURE_BORDER_COLOR, borderColor);

    return texture;
}
