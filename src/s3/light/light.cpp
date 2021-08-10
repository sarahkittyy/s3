#include "s3/light/light.hpp"

namespace s3::light {

light::light(glm::vec3 pos)
	: m_position(pos),
	  m_ambient(0.1f),
	  m_diffuse(0.5f),
	  m_specular(1.0f) {
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

void light::set_ambient(glm::vec3 ambient) {
	m_ambient = ambient;
}

glm::vec3 light::get_ambient() const {
	return m_ambient;
}

void light::set_diffuse(glm::vec3 diffuse) {
	m_diffuse = diffuse;
}

glm::vec3 light::get_diffuse() const {
	return m_diffuse;
}

void light::set_specular(glm::vec3 specular) {
	m_specular = specular;
}

glm::vec3 light::get_specular() const {
	return m_specular;
}

void light::populate(const char* context, shader& s) const {
	fill(context, "position", m_position, s);
	fill(context, "ambient", m_ambient, s);
	fill(context, "diffuse", m_diffuse, s);
	fill(context, "specular", m_specular, s);
}

}
