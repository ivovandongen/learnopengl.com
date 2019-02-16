#include <utility>

#pragma once

#include <glad/glad.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using ProcAddress = void (*)();
using ExtensionLoadFN = std::function<ProcAddress(const char *)>;

template<class>
class ExtensionFunction;

template<class R, class... Args>
class ExtensionFunction<R(Args...)> {
public :
    explicit ExtensionFunction(ProcAddress address)
            : _address(address) {
    }

    R operator()(Args... args) const {
        return (*reinterpret_cast<R(*)(Args...)>(_address))(std::forward<Args>(args)...);
    }

    explicit operator bool() const {
        return _address != nullptr;
    }

private:
    ProcAddress _address = nullptr;
};

class Extensions {
public:
    explicit Extensions(ExtensionLoadFN fn)
            : loader(std::move(fn)) {
    };

    ProcAddress load(const std::vector<std::pair<std::string, std::string>> &extension) const {
        const static auto extensionAvailable = [this](const std::string &name) -> bool {
            const static auto extensions = availableExtensions();
            const static bool _ = [this] {
                for (auto &ext:extensions) {
                    std::cout << ext << std::endl;
                }
                return false;
            }();

            return std::find(std::begin(extensions), std::end(extensions), name) != std::end(extensions);
        };

        ProcAddress address = nullptr;
        for (const auto &alt : extension) {
            if (extensionAvailable(alt.first) && (address = loader(alt.second.c_str()))) {
                return address;
            }
        }

        return nullptr;
    }

private:

    static std::vector<std::string> availableExtensions() {
        std::vector<std::string> extensions;

        GLint n;
        glGetIntegerv(GL_NUM_EXTENSIONS, &n);
        for (GLuint i = 0; i < n; i++) {
            extensions.emplace_back(reinterpret_cast<const char *>(glGetStringi(GL_EXTENSIONS, i)));
        }

        return extensions;
    }

private:
    ExtensionLoadFN loader;
};