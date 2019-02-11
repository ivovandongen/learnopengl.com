#include "framebuffer.hpp"

#include <cassert>

namespace {

void bindFramebuffer(GLuint id, Framebuffer::BindMode mode) {
    switch (mode) {
        case Framebuffer::BindMode::READ:
            glBindFramebuffer(GL_READ_FRAMEBUFFER, id);
            break;
        case Framebuffer::BindMode::DRAW:
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, id);
            break;
        default:
            glBindFramebuffer(GL_FRAMEBUFFER, id);
    }
}

} // namespace

void Framebuffer::bindDefault(Framebuffer::BindMode mode) {
    bindFramebuffer(0, mode);
}

Framebuffer::Framebuffer(unsigned int width, unsigned int height, unsigned int samples) {
    glGenFramebuffers(1, &_id);

    bind();

    // Add a texture for the color attachment
    _texture.emplace(width, height, samples);

    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           samples > 1 ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D,
                           _texture->id(),
                           0);

    // Attach a renderbuffer for the depth and stencil buffers
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    if (samples > 1) {
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height);
    } else {
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    }
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    assert(ready());
}

Framebuffer::~Framebuffer() {
    if (rbo) {
        glDeleteRenderbuffers(1, &rbo);
    }
    _texture.reset();
    glDeleteFramebuffers(1, &_id);
}

void Framebuffer::bind(Framebuffer::BindMode mode) const {
    bindFramebuffer(_id, mode);
}

void Framebuffer::unbind() const {
    bindDefault();
}

bool Framebuffer::bound() const {
    GLint fbo;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &fbo);
    return _id == fbo;
}

bool Framebuffer::ready() const {
    assert(bound());
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

const Texture &Framebuffer::texture() {
    assert(_texture);
    return _texture.value();
}
