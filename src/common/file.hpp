#pragma once

#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

std::string readFile(const std::string &fileName) {

    std::ifstream t(fileName);
    std::string result;

    if (t.is_open()) {
        t.seekg(0, std::ios::end);
        result.reserve(t.tellg());
        t.seekg(0, std::ios::beg);

        result.assign((std::istreambuf_iterator<char>(t)),
                      std::istreambuf_iterator<char>());
    } else {
        std::cerr << "Could not open file: " << fileName << std::endl;
    }

    return result;
}
