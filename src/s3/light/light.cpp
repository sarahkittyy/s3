#include "s3/light/light.hpp"

namespace s3::light {

light::light(glm::vec3 pos)
	: m_position(pos),
	  m_ambient(color::grey_norm(0.1f)),
	  m_diffuse(color::grey_norm(0.5f)),
	  m_specular(color::grey_norm(1.0f)) {
}

light::light(float x, float y, float z)
	: light(glm::vec3(x, y, z)) {
}

void light::set_pos(glm::vec3 pos) {
	m_position = pos;
}

glm::vec3 light::get_pos() const {
	return m_position;
}

void light::set_ambient(color ambient) {
	m_ambient = ambient;
}

color light::get_ambient() const {
	return m_ambient;
}

void light::set_diffuse(color diffuse) {
	m_diffuse = diffuse;
}

color light::get_diffuse() const {
	return m_diffuse;
}

void light::set_specular(color specular) {
	m_specular = specular;
}

color light::get_specular() const {
	return m_specular;
}

void light::populate(const char* context, shader& s) const {
	fill(context, "position", m_position, s);
	fill(context, "ambient", (glm::vec3)m_ambient, s);
	fill(context, "diffuse", (glm::vec3)m_diffuse, s);
	fill(context, "specular", (glm::vec3)m_specular, s);
}

}
