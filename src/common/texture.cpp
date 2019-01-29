#include "texture.hpp"

#include <stb_image.h>

Texture::Texture(const Image &image, bool generateMipmap) {
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    auto format = image.channels() == 3 ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, image.width(), image.height(), 0, format, GL_UNSIGNED_BYTE, image.data());

    if (generateMipmap) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &_id);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
