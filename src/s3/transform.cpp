#include "s3/transform.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace s3 {

transform::transform()
	: m_trans(0.f),
	  m_rot(glm::vec3(0, 0, 0)),
	  m_scale(1, 1, 1) {
}

transform::~transform() {
}

void transform::move(glm::vec3 by) {
	m_trans += by;
}

void transform::set_pos(glm::vec3 pos) {
	m_trans = pos;
}

glm::vec3 transform::get_pos() const {
	return m_trans;
}

void transform::rotate(glm::vec3 euler) {
	m_rot *= glm::quat(euler);
}

void transform::set_rotation(glm::vec3 euler) {
	m_rot = glm::quat(euler);
}

glm::vec3 transform::get_euler_rotation() const {
	return glm::eulerAngles(m_rot);
}

void transform::scale(glm::vec3 by) {
	m_scale += by;
}

void transform::set_scale(glm::vec3 scale) {
	m_scale = scale;
}

glm::vec3 transform::get_scale() const {
	return m_scale;
}

transform transform::operator*(const transform& other) const {
	transform n;
	n.m_rot	  = m_rot * other.m_rot;
	n.m_trans = m_trans + other.m_trans;
	n.m_scale = m_scale * other.m_scale;
	return n;
}

transform& transform::operator*=(const transform& other) {
	m_trans += other.m_trans;
	m_rot *= other.m_rot;
	m_scale *= other.m_scale;
	return *this;
}

glm::mat4 transform::matrix() const {
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_trans);
	glm::mat4 rot	= glm::toMat4(m_rot);
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_scale);
	return trans * rot * scale;
}

}
