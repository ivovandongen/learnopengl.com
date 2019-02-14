#pragma once

template<class T, T DEFAULT = T()>
class ID {
public:
    ID() = default;

    explicit ID(T id) : _id(id) {
    }

    ID(const ID &) = delete;

    ID(ID &&o) noexcept : _id(o._id) {
        o._id = DEFAULT;
    }

    ID &operator=(const ID &) = delete;

    ID &operator=(ID &&o) noexcept {
        _id = o._id;
        _id = DEFAULT;
        return *this;
    }

    T &operator->() {
        return _id;
    }

    T &operator*() {
        return _id;
    }

    const T &operator->() const {
        return _id;
    }

    const T &operator*() const {
        return _id;
    }

    explicit operator bool() const {
        return _id != DEFAULT;
    }

private:
    T _id{DEFAULT};
};
