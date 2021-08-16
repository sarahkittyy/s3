#include "s3/light/base.hpp"

namespace s3::light {

base::base()
	: m_ambient(color::grey_norm(0.03f)),
	  m_diffuse(color::grey_norm(0.5f)),
	  m_specular(color::grey_norm(1.0f)) {
}

base::~base() {
}

void base::set_ambient(color ambient) {
	m_ambient = ambient;
}

color base::get_ambient() const {
	return m_ambient;
}

void base::set_diffuse(color diffuse) {
	m_diffuse = diffuse;
}

color base::get_diffuse() const {
	return m_diffuse;
}

void base::set_specular(color specular) {
	m_specular = specular;
}

color base::get_specular() const {
	return m_specular;
}

void base::populate(const char* context, shader& s) const {
	fill(context, "ambient", (glm::vec3)m_ambient, s);
	fill(context, "diffuse", (glm::vec3)m_diffuse, s);
	fill(context, "specular", (glm::vec3)m_specular, s);
}

}
