#pragma once

#include <string>

class Image {
public:
    explicit Image(const std::string &path, bool flipOnLoad = true);

    ~Image();

    const unsigned char *data() const {
        return _data;
    }

    const int width() const {
        return _width;
    }

    const int height() const {
        return _height;
    }

    const int channels() const {
        return _channels;
    }

private:
    int _width{0}, _height{0}, _channels{0};
    unsigned char *_data = nullptr;
};