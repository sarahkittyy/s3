#include "s3/rendertarget.hpp"

#include <stdexcept>

#include <s3/renderable.hpp>

namespace s3 {

rendertarget::rendertarget(int width, int height)
	: m_width(width),
	  m_height(height) {
}

rendertarget::~rendertarget() {
}

void rendertarget::flush(color col) {
	bind();
	glViewport(0, 0, m_width, m_height);
	glClearColor(col.r, col.g, col.b, col.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void rendertarget::draw(renderable& d, drawstate ds) {
	bind();
	d.draw(*this, ds);
}

glm::vec2 rendertarget::size() const {
	return glm::vec2(m_width, m_height);
}

void rendertarget::set_width(int width) {
	m_width = width;
}

void rendertarget::set_height(int height) {
	m_height = height;
}

void rendertarget::set_size(glm::vec2 size) {
	set_width(size.x);
	set_height(size.y);
}

GLuint rendertarget::framebuffer() const {
	return 0;
}

void rendertarget::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool rendertarget::valid() {
	bind();
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void rendertarget::reset_opengl() {
	bind();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_MULTISAMPLE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glFrontFace(GL_CCW);
}

}
