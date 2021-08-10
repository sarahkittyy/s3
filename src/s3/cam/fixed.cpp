#include "s3/cam/fixed.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace s3::cams {

fixed::fixed(glm::vec3 pos, glm::vec3 aim)
	: m_pos(pos),
	  m_aim(aim) {
}

fixed::~fixed() {
}

void fixed::set_pos(glm::vec3 pos) {
	m_pos = pos;
}

glm::vec3 fixed::get_pos() const {
	return m_pos;
}

void fixed::set_aim(glm::vec3 aim) {
	m_aim = aim;
}

glm::vec3 fixed::get_aim() const {
	return m_aim;
}

glm::mat4 fixed::proj(const rendertarget& target) const {
	return glm::perspective(glm::radians(45.f),
							target.size().x / target.size().y,
							0.1f,
							100.f);
}

glm::mat4 fixed::view(const rendertarget& target) const {
	return glm::lookAt(m_pos, m_aim, glm::vec3(0, 1, 0));
}

glm::vec3 fixed::position() const {
	return m_pos;
}

}
