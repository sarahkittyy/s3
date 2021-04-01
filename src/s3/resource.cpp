#include "s3/resource.hpp"

namespace s3 {

s3::texture& resource::texture(const std::string& path) {
	if (!m_tex.contains(path)) {
		m_tex[path].from_file(path);
	}
	return m_tex[path];
}

}
