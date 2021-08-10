#include "s3/material.hpp"

namespace s3 {

material::material()
	: m_diffuse(nullptr),
	  m_specular(nullptr),
	  m_shininess(32.f) {
}

material::~material() {
}

void material::set_diffuse(const texture& diffuse) {
	m_diffuse = &diffuse;
}

const texture& material::get_diffuse() const {
	return *m_diffuse;
}

void material::set_specular(const texture& specular) {
	m_specular = &specular;
}

const texture& material::get_specular() const {
	return *m_specular;
}

void material::set_texture(const texture& tex) {
	set_diffuse(tex);
	set_specular(tex);
}

void material::set_shininess(float shininess) {
	m_shininess = shininess;
}

float material::get_shininess() const {
	return m_shininess;
}

void material::populate(const char* context, shader& s) const {
	fill(context, "shininess", m_shininess, s);

	s.set_uniform("material.diffuse", 0);
	s.set_uniform("material.specular", 1);

	if (m_diffuse) {
		m_diffuse->bind(0);
	} else {
		texture::unbind(0);
	}

	if (m_specular) {
		m_specular->bind(1);
	} else {
		texture::unbind(1);
	}
}

}
