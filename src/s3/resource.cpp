#include "s3/resource.hpp"

#include <sstream>

namespace s3 {

resource::resource() noexcept
	: m_tex(),
	  m_shdr() {
}

s3::texture& resource::texture(const std::string& path) {
	if (!m_tex.contains(path)) {
		m_tex[path].from_file(path);
	}
	return m_tex[path];
}

s3::shader& resource::shader(const char* vs, const char* fs) {
	std::ostringstream ss;
	ss << (const void*)vs;
	ss << (const void*)fs;
	std::string key = ss.str();
	if (!m_shdr.contains(key)) {
		m_shdr.emplace(key, s3::shader(vs, fs));
	}
	return m_shdr[key];
}

}
