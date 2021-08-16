#include "s3/light/dir.hpp"

namespace s3::light {

dir::dir(glm::vec3 dir)
	: m_dir(dir) {
}

dir::dir(float x, float y, float z)
	: m_dir(glm::vec3(x, y, z)) {
}

void dir::set_dir(glm::vec3 dir) {
	m_dir = dir;
}

void dir::set_dir(float x, float y, float z) {
	m_dir = glm::vec3(x, y, z);
}

glm::vec3 dir::get_dir() const {
	return m_dir;
}

void dir::populate(const char* context, shader& s) const {
	base::populate(context, s);
	fill(context, "direction", m_dir, s);
}

}
