#include "s3/rendertexture.hpp"

#include <stdexcept>

namespace s3 {

rendertexture::rendertexture(int width, int height)
	: rendertarget(width, height),
	  m_fbo(0),
	  m_rbo(0) {
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

rendertexture::~rendertexture() {
	if (m_fbo != 0) {
		glDeleteFramebuffers(1, &m_fbo);
	}
	if (m_rbo != 0) {
		glDeleteRenderbuffers(1, &m_rbo);
	}
}

void rendertexture::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

}
