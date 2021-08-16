#include "s3/light/spot.hpp"

#include <cmath>

namespace s3::light {

spot::spot()
	: m_pos(0, 10.f, 0),
	  m_dir(0, -1.f, 0),
	  m_angle(24.5f),
	  m_feather(12.f),
	  m_constant(1.0f),
	  m_linear(0.045f),
	  m_quadratic(0.0075f) {
}

void spot::populate(const char* context, shader& s) const {
	base::populate(context, s);
	fill(context, "position", m_pos, s);
	fill(context, "direction", m_dir, s);
	fill(context, "innerAngle", std::cos(glm::radians(m_angle - (m_feather / 2.f))), s);
	fill(context, "outerAngle", std::cos(glm::radians(m_angle + (m_feather / 2.f))), s);

	fill(context, "constant", m_constant, s);
	fill(context, "linear", m_linear, s);
	fill(context, "quadratic", m_quadratic, s);
}

void spot::set_pos(glm::vec3 pos) {
	m_pos = pos;
}

void spot::set_pos(float x, float y, float z) {
	m_pos = glm::vec3(x, y, z);
}

glm::vec3 spot::get_pos() const {
	return m_pos;
}

void spot::set_dir(glm::vec3 dir) {
	m_dir = dir;
}

void spot::set_dir(float x, float y, float z) {
	m_dir = glm::vec3(x, y, z);
}

glm::vec3 spot::get_dir() const {
	return m_dir;
}

void spot::set_angle(float angle) {
	m_angle = angle;
}

float spot::get_angle() const {
	return m_angle;
}

void spot::set_feather_strength(float feather) {
	m_feather = feather;
}

float spot::get_feather_strength() const {
	return m_feather;
}

void spot::set_attenuation(float constant, float linear, float quadratic) {
	m_constant	= constant;
	m_linear	= linear;
	m_quadratic = quadratic;
}

}
