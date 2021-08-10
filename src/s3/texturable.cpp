#include "s3/texturable.hpp"

namespace s3 {

texturable::texturable() {
}

texturable::~texturable() {
}

void texturable::set_texture(const s3::texture& tex) {
	m_tex = &tex;
}

const s3::texture* texturable::texture() const {
	return m_tex;
}

bool texturable::has_texture() const {
	return m_tex != nullptr;
}

}
