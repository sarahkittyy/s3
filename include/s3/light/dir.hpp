#pragma once

#include <s3/light/base.hpp>

namespace s3::light {

/// directional light source, i.e. the sun.
class dir : public base {
public:
	/// constructs the light with a direction
	dir(glm::vec3 dir = glm::vec3(0, -1, 0));
	/// constructs the light with a direction
	dir(float x, float y, float z);

	/// set the light direction
	void set_dir(glm::vec3 dir);
	/// set the light direction
	void set_dir(float x, float y, float z);
	/// get the light direction
	glm::vec3 get_dir() const;

	/// populate the shader
	void populate(const char* context, shader& s) const;

private:
	/// the light direction
	glm::vec3 m_dir;
};

}
