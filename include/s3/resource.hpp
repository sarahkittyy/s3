#pragma once

#include <s3/shader.hpp>
#include <s3/texture.hpp>

#include <string>
#include <unordered_map>

namespace s3 {

/// handles the loading of resources to prevent excessive reads
class resource {
public:
	/// retrive a texture given a path to the image
	s3::texture& texture(const std::string& path);

private:
	std::unordered_map<std::string, s3::texture> m_tex;
};

}
