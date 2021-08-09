#include "s3/rendertarget.hpp"

#include <stdexcept>

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

void rendertarget::draw(mesh& m, drawstate ds) {
	bind();
	if (ds.shader) {
		ds.shader->use();
	} else {
		throw std::runtime_error("Cannot render without a shader!");
	}
	if (ds.texture) {
		ds.texture->bind();
	} else {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if (ds.camera) {
		ds.camera->update();
		ds.shader->set_uniform("proj", ds.camera->proj(*this));
		ds.shader->set_uniform("view", ds.camera->view(*this));
	} else {
		throw std::runtime_error("Cannot render without a camera!");
	}
	ds.shader->set_uniform("model", ds.transform.matrix());
	m.draw();
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glFrontFace(GL_CCW);
}

}
