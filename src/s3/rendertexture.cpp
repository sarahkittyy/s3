#include "s3/rendertexture.hpp"

#include <stdexcept>

namespace s3 {

rendertexture::rendertexture(int width, int height)
	: rendertarget(width, height),
	  m_fbo(0) {
	glGenFramebuffers(1, &m_fbo);

	rendertexture::bind();
	reset_opengl();

	create(width, height);
	texture::bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, handle(), 0);

	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

	if (!valid()) throw std::runtime_error("Failure initializing rendertexture.");
}

void rendertexture::del() {
	if (m_fbo == 0) {
		throw std::runtime_error("Cannot delete framebuffer of id 0 (maybe you forgot to call create()?)");
	}
	glDeleteFramebuffers(1, &m_fbo);

	if (m_rbo == 0) {
		throw std::runtime_error("Cannot delete renderbuffer of id 0 (maybe you forgot to call create()?)");
	}
	glDeleteRenderbuffers(1, &m_rbo);

	texture::del();
}

void rendertexture::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

}
