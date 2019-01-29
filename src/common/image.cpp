# include "image.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include <iostream>

Image::Image(const std::string &path, bool flipOnLoad) {
    std::cout << "Loading image: " << path << " flipped: " << flipOnLoad << std::endl;

    if (flipOnLoad) {
        stbi_set_flip_vertically_on_load(true);
    }

    _data = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);
    if (!_data) {
        std::cerr << "Could not read file: " << path << std::endl;
    }

    // Set flags back
    stbi_set_flip_vertically_on_load(false);
}

Image::~Image() {
    stbi_image_free(_data);
}

