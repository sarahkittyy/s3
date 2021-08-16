#include "s3/light/point.hpp"

namespace s3::light {

point::point()
	: point(glm::vec3(0, 10, 0)) {
}

point::point(glm::vec3 pos)
	: m_pos(pos),
	  m_constant(1.0f),
	  m_linear(0.045f),
	  m_quadratic(0.0075f) {
}

point::point(float x, float y, float z)
	: point(glm::vec3(x, y, z)) {
}

void point::set_pos(glm::vec3 pos) {
	m_pos = pos;
}

void point::set_pos(float x, float y, float z) {
	m_pos = glm::vec3(x, y, z);
}

glm::vec3 point::get_pos() const {
	return m_pos;
}

void point::set_attenuation(float constant, float linear, float quadratic) {
	m_constant	= constant;
	m_linear	= linear;
	m_quadratic = quadratic;
}

void point::populate(const char* context, shader& s) const {
	base::populate(context, s);
	fill(context, "position", m_pos, s);
	fill(context, "constant", m_constant, s);
	fill(context, "linear", m_linear, s);
	fill(context, "quadratic", m_quadratic, s);
}

}
