#include "s3/material.hpp"

namespace s3 {

material::material()
	: m_diffuse(nullptr),
	  m_specular(nullptr),
	  m_emission(nullptr),
	  m_shininess(32.f) {
}

material::~material() {
}

void material::set_diffuse(texture& diffuse) {
	m_diffuse = &diffuse;
}

texture* material::get_diffuse() {
	return m_diffuse;
}

void material::set_specular(texture& specular) {
	m_specular = &specular;
}

texture* material::get_specular() {
	return m_specular;
}

void material::set_emission(texture& emission) {
	m_emission = &emission;
}

texture* material::get_emission() {
	return m_emission;
}

void material::set_texture(texture& tex) {
	set_diffuse(tex);
	set_specular(tex);
}

void material::set_shininess(float shininess) {
	m_shininess = shininess;
}

float material::get_shininess() const {
	return m_shininess;
}

void material::clear() {
	m_diffuse	= nullptr;
	m_specular	= nullptr;
	m_emission	= nullptr;
	m_shininess = 32;
}

void material::populate(const char* context, shader& s) const {
	fill(context, "shininess", m_shininess, s);

	s.set_uniform("material.diffuse", 0);
	s.set_uniform("material.specular", 1);
	s.set_uniform("material.emission", 2);

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

	if (m_emission) {
		m_emission->bind(2);
	} else {
		texture::unbind(2);
	}
}

}
