#include "texture.hpp"

#include <stb_image.h>

Texture::Texture(const Image &image, bool generateMipmap) {
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format;
    switch (image.channels()) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            format = GL_RGB;
    }


    glTexImage2D(GL_TEXTURE_2D, 0, format, image.width(), image.height(), 0, format, GL_UNSIGNED_BYTE, image.data());

    if (generateMipmap) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

Texture::Texture(unsigned int width, unsigned int height) {
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture() {
    glDeleteTextures(1, &_id);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
