#include "s3/rendertarget.hpp"

#include <stdexcept>

namespace s3 {

rendertarget::rendertarget()
	: m_fbo(0) {
	bind();
	// TODO: these options
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glFrontFace(GL_CCW);
}

rendertarget::~rendertarget() {
}

void rendertarget::flush(color col) {
	bind();
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
	}
	if (ds.camera) {
		ds.camera->update();
		ds.shader->set_uniform("proj", ds.camera->proj());
		ds.shader->set_uniform("view", ds.camera->view());
	} else {
		throw std::runtime_error("Cannot render without a camera!");
	}
	ds.shader->set_uniform("model", ds.transform.matrix());
	m.draw();
}

void rendertarget::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

bool rendertarget::valid() {
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

}
