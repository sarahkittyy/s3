#include "s3/rendertexture.hpp"

#include <stdexcept>

namespace s3 {

rendertexture::rendertexture(int width, int height, texture_type type)
	: rendertarget(width, height),
	  texture(type),
	  m_fbo(0),
	  m_rbo(0) {
	glGenFramebuffers(1, &m_fbo);

	rendertexture::bind();
	reset_opengl();

	create(width, height);
	texture::bind();
	if (get_type() == texture_type::DEFAULT) {
		glFramebufferTexture2D(GL_FRAMEBUFFER,
							   GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, handle(), 0);

		glGenRenderbuffers(1, &m_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
	} else if (get_type() == texture_type::MULTISAMPLE) {
		glFramebufferTexture2D(GL_FRAMEBUFFER,
							   GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, handle(), 0);

		glGenRenderbuffers(1, &m_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
		/// TODO: setting to toggle sampling and count
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
	} else {
		throw std::runtime_error("Texture type not supported by the rendertexture.");
	}

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

void rendertexture::blit(GLuint fbo, int target_width, int target_height) {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glBlitFramebuffer(
		// src
		0, 0, size().x, size().y,
		// dest
		0, 0, target_width, target_height,
		GL_COLOR_BUFFER_BIT,
		GL_NEAREST);
}

void rendertexture::blit(rendertarget& other) {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, other.framebuffer());
	glBlitFramebuffer(
		// src
		0, 0, size().x, size().y,
		// dest
		0, 0, other.size().x, other.size().y,
		GL_COLOR_BUFFER_BIT,
		GL_NEAREST);
}

GLuint rendertexture::framebuffer() const {
	return m_fbo;
}

void rendertexture::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

}
