#pragma once

#include <glm/glm.hpp>
#include <s3/color.hpp>

namespace s3 {

/// standard vertex passed to the shader.
struct vertex {
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 norm;
};

}
